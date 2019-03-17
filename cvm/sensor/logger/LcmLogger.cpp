#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <linux/limits.h>
#include <getopt.h>
#include <inttypes.h>

#include <map>
#include <thread>
#include <mutex>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/Logging.h>
#include <cvm/base/BlockingQueue.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Timestamp.h>

namespace cvm
{

namespace sensor
{

namespace logger
{

namespace internal
{

void deleter(lcm::LogEvent* logEvent)
{
    delete[] reinterpret_cast<char*>(logEvent->data);
    delete logEvent;
}

}

class Logger : public base::NonCopyable
{
public:
    Logger(const std::string& lcmUrl,
           const std::string& outputFilename,
           double autoSplitMB, bool forceOverwrite,
           bool autoIncrement, bool useStrftime,
           const std::string& chanRegex, int maxWriteQueueSizeMB,
           bool invertChannels, int fflushIntervalMilisecond,
           bool quiet, bool append);
    ~Logger();

    void loop();

private:
    typedef std::unique_ptr<lcm::LogEvent,
                            std::function<void(lcm::LogEvent*)>> LogEventPtr;
    void openLogfile();
    void writeData();
    void messageHandler(const lcm::ReceiveBuffer* rbuf,
                        const std::string& channel);

    lcm::LCM _lcm;

    std::unique_ptr<lcm::LogFile> _log;
    std::string _outputFilename;
    std::string _fname;
    std::string _outputFilenamePrefix;

    const double _autoSplitMB;
    const bool _forceOverwrite;
    const bool _useStrftime;
    const int _fflushIntervalMilisecond;
    const int64_t _maxWriteQueueSize;
    const bool _autoIncrement;
    int _nextIncrementNum;

    int64_t _droppedPacketsCount;
    int64_t _lastDropReportMicrosecond;
    int64_t _lastDropReportCount;

    const bool _quiet;
    const bool _append;

    // variables for inverted matching (e.g., logging all but some channels)
    const int _invertChannels;
    const std::string _chanRegex;

    // these members controlled by mutex
    int64_t _writeQueueSize;
    bool _writeThreadExitFlag;

    std::thread _writeThread;
    cvm::base::BlockingQueue<LogEventPtr> _dataQueue;
    std::mutex _mutex;

    // these members controlled by write thread
    int64_t nevents;
    int64_t logsize;
    int64_t eventsSinceLastReport;
    int64_t startTime;
    int64_t lastReportTime;
    int64_t lastReportLogsize;
    int64_t lastFflushTime;
    int64_t lastSpewTimeMicrosecond;
    int     numSplits;

};

Logger::Logger(const std::string& lcmUrl,
               const std::string& outputFilename,
               double autoSplitMB, bool forceOverwrite,
               bool autoIncrement, bool useStrftime,
               const std::string& chanRegex, int maxWriteQueueSizeMB,
               bool invertChannels, int fflushIntervalMilisecond,
               bool quiet, bool append)
    : _autoSplitMB(autoSplitMB), _forceOverwrite(forceOverwrite),
      _outputFilename(outputFilename), _nextIncrementNum(0),
      _invertChannels(invertChannels),
      _fflushIntervalMilisecond(fflushIntervalMilisecond),
      _autoIncrement(autoIncrement), _useStrftime(useStrftime),
      _maxWriteQueueSize(maxWriteQueueSizeMB * (1 << 20)),
      _lcm(lcmUrl), _quiet(quiet), _append(append),
      _droppedPacketsCount(0),
      _lastDropReportMicrosecond(0),
      _lastDropReportCount(0),
      nevents(0),
      logsize(0),
      eventsSinceLastReport(0),
      startTime(base::Timestamp::now().microSecondsSinceEpoch()),
      lastReportTime(startTime),
      lastReportLogsize(0),
      lastFflushTime(startTime),
      lastSpewTimeMicrosecond(startTime),
      numSplits(0)

{
    if (!_lcm.good()) {
        DIE("Couldn't initialize LCM!");
    }

    if(_invertChannels) {
        // if inverting the channels, subscribe to everything and invert on the
        // callback
        _lcm.subscribe(".*", &Logger::messageHandler, this);
    } else {
        // otherwise, let LCM handle the regex
        _lcm.subscribe(chanRegex, &Logger::messageHandler, this);
    }
}

Logger::~Logger()
{
    {
        // stop the write thread
        std::unique_lock<std::mutex> lock(_mutex);
        _writeThreadExitFlag = true;
    }
    _writeThread.join();
}

void Logger::loop()
{
    _writeThread = std::move(std::thread(std::bind(&Logger::writeData, this)));

    while (_lcm.handle() == 0) {
        ;
    }
}

void Logger::openLogfile()
{
    // maybe run the filename through strftime
    if (_useStrftime) {
        char newPrefix[PATH_MAX];
        time_t now = time (NULL);
        strftime(newPrefix, sizeof(newPrefix),
                _outputFilename.data(), localtime(&now));

        // If auto-increment is enabled and the strftime-formatted filename
        // prefix has changed, then reset the auto-increment counter.
        if(_autoIncrement && (newPrefix == _outputFilenamePrefix))
            _nextIncrementNum = 0;
        _outputFilenamePrefix = newPrefix;
    } else {
        _outputFilenamePrefix = _outputFilename;
    }

    if (_autoIncrement) {
        /* Loop through possible file names until we find one that doesn't
         * already exist.  This way, we never overwrite an existing file. */
        char fname[PATH_MAX];
        do {
            snprintf(fname, sizeof(fname), "%s.%02d",
                    _outputFilenamePrefix.data(), _nextIncrementNum);
            _nextIncrementNum++;
        } while(access(fname, F_OK) == 0);
        _fname = fname;
    }else {
        _fname = _outputFilenamePrefix;
        if (!(_forceOverwrite || _append)) {
            if (access(_fname.data(), F_OK) == 0) {
                DIE("Refusing to overwrite existing file \"%s\"\n", _fname.data());
            }
        }
    }

    if(!_quiet) {
        printf("Opening log file \"%s\"\n", _fname.data());
    }

    // open output file in append mode if we're rotating log files or appending
    // use write mode if not.
    const char* logmode = _append ? "a" : "w";
    _log.reset(new lcm::LogFile(_fname, logmode));
    if (!_log) {
        DIE("Error: fopen failed");
    }
}

void Logger::writeData()
{

    openLogfile();

    while(1) {
        auto data = std::move(_dataQueue.dequeueWithMove());


        // Is it time to start a new logfile?
        bool split = false;
        if(_autoSplitMB) {
          double logsizeMB = (double)logsize / (1 << 20);
          split = (logsizeMB >= _autoSplitMB);
        }

        if(split) {
            // Yes.  open up a new log fie
            openLogfile();
            numSplits++;
            logsize = 0;
            lastReportLogsize = 0;
        }

        {
            std::unique_lock<std::mutex> lock(_mutex);
            // Should the write thread exit?
            if(_writeThreadExitFlag) {
                return;
            }

            // nope.  write the event to disk
            int64_t sz = sizeof(lcm::LogEvent) + data->channel.length() + data->datalen;
            _writeQueueSize -= sz;
        }

        if(_log->writeEvent(&*data) != 0) {
            char reason[1024];
            strerror_r(errno, reason, sizeof(reason));
            int64_t now = base::Timestamp::now().microSecondsSinceEpoch();
            if((now - lastSpewTimeMicrosecond) > 500000) {
                fprintf(stderr, "LcmFile::writeEvent : %s\n", reason);
                lastSpewTimeMicrosecond = now;
            }
            if(errno == ENOSPC) {
                DIE("No enough space");
            }else {
                continue;
            }
        }

        if (_fflushIntervalMilisecond >= 0 &&
            (data->timestamp - lastFflushTime) > _fflushIntervalMilisecond*1000) {
            fflush(_log->getFilePtr());
            // Perform a full fsync operation after flush
            fdatasync(fileno(_log->getFilePtr()));
            lastFflushTime = data->timestamp;
        }

        // bookkeeping, cleanup
        nevents++;
        eventsSinceLastReport++;
        logsize += sizeof(lcm::LogEvent) + data->channel.length() + data->datalen;

        if (!_quiet && (data->timestamp - lastReportTime > 1000000)) {
            double dt = (data->timestamp - lastReportTime) / 1000000.0;
            double tps =  eventsSinceLastReport / dt;
            double kbps = (logsize - lastReportLogsize) / (dt * 1024.0);
            printf("Summary: %s ti:%4" PRIi64 "sec Events: %-9" PRIi64
                   " ( %4" PRIi64 " MB )      TPS: %8.2f       KB/s: %8.2f\n",
                    _fname.data(), (int64_t)dt,
                    nevents, logsize/1048576, tps, kbps);
            lastReportTime = data->timestamp;
            eventsSinceLastReport = 0;
            lastReportLogsize = logsize;
        }
    }
}

void Logger::messageHandler (const lcm::ReceiveBuffer* rbuf,
                              const std::string& channel)
{
    if(_invertChannels) {
        //if(g_regex_match(regex, channel, (GRegexMatchFlags) 0, NULL))
        //    return;
    }

    int channellen = channel.length();

    // check if the backlog of unwritten messages is too big.  If so, then
    // ignore this event
    bool dropped = false;

    // !!!!
    int64_t memSize = sizeof(lcm::LogEvent) + channellen + 1 + rbuf->data_size;
    {
        std::unique_lock<std::mutex> lock(_mutex);
        int memRequired = memSize + _writeQueueSize;
        if(memRequired > _maxWriteQueueSize) {
            dropped = true;
        }else {
            _writeQueueSize = memRequired;
        }
    }

    if(dropped) {
        // can't write to logfile fast enough.  drop packet.
        // maybe print an informational message to stdout
        int64_t now = base::Timestamp::now().microSecondsSinceEpoch();
        _droppedPacketsCount++;
        int rc = _droppedPacketsCount - _lastDropReportCount;

        if((now - _lastDropReportMicrosecond > 1000000) && (rc > 0)) {
            if(!_quiet)
                printf("Can't write to log fast enough.  Dropped %d packet%s\n",
                        rc, rc==1?"":"s");
            _lastDropReportMicrosecond = now;
            _lastDropReportCount = _droppedPacketsCount;
        }
        return;
    }

    LogEventPtr data(new lcm::LogEvent, std::function<void(lcm::LogEvent*)>(internal::deleter));

    data->timestamp = rbuf->recv_utime;
    data->datalen = rbuf->data_size;

    // log_write_event will handle le.eventnum.
    data->channel = channel;
    data->data = reinterpret_cast<void*>(new char[rbuf->data_size]);
    memcpy(data->data, rbuf->data, rbuf->data_size);

    // queue up the message for writing to disk by the write thread
    _dataQueue.enqueue(std::move(data));
}

}

}

}

void usage ()
{
    fprintf (stderr, "usage: lcm-logger [options] [FILE]\n"
            "\n"
            "    CVM message logging utility.  Subscribes to all channels on an LCM\n"
            "    network, and records all messages received on that network to\n"
            "    FILE.  If FILE is not specified, then a filename is automatically\n"
            "    chosen.\n"
            "\n"
            "Options:\n"
            "\n"
            "  -c, --channel=CHAN         Channel string to pass for subscription.\n"
            "                             (default: \".*\")\n"
            "      --flush-interval=MS    Flush the log file to disk every MS milliseconds.\n"
            "                             (default: 100)\n"
            "  -f, --force                Overwrite existing files\n"
            "  -h, --help                 Shows this help text and exits\n"
            "  -i, --increment            Automatically append a suffix to FILE\n"
            "                             such that the resulting filename does not\n"
            "                             already exist.  This option precludes -f \n"
            "  -l, --lcm-url=URL          Log messages on the specified LCM URL\n"
            "  -m, --max-unwritten-mb=SZ  Maximum size of received but unwritten\n"
            "                             messages to store in memory before dropping\n"
            "                             messages.  (default: 100 MB)\n"
            "      --split-mb=N           Automatically start writing to a new log\n"
            "                             file once the log file exceeds N MB in size\n"
            "                             (can be fractional).  This option requires -i.\n"
            "  -q, --quiet                Suppress normal output and only report errors.\n"
            "  -a, --append               Append events to the given log file.\n"
            "  -s, --strftime             Format FILE with strftime.\n"
            "  -v, --invert-channels      Invert channels.  Log everything that CHAN\n"
            "                             does not match.\n"
            "\n"
            "Splitting log files\n"
            "==============================\n"
            "    For long-term logging, lcm-logger can split log files automatically, \n"
            "    moving to a new log file.\n"
            "    To do this, use --split-mb.  For example:\n"
            "\n"
            "        lcm-logger --split-mb=2 logfile\n"
            "\n");
}

//std::map<int, std::function<void()> signalCallbacks;
//void signalHandler(int signo)
//{
//    auto it = signalCallbacks.find(signo);
//    if (it != signalCallbacks.end()) {
//        it->second();
//    }
//}

//void setSignalCallback(int signo, std::function<void()> signalCallback)
//{
//    signal(signo, signalHandler);
//    signalCallbacks[signo] = signalCallback;
//}

int main(int argc, char *argv[])
{

    setlinebuf (stdout);

    // Parse command line
    double autoSplitMB = 0;
    bool forceOverwrite = false;
    bool autoIncrement = false;
    bool useStrftime = false;
    std::string chanRegex(".*");
    double maxWriteQueueSizeMB = 500;
    bool invertChannels = false;
    int fflushIntervalMicrosecond = 100;
    bool quiet = false;
    bool append = false;
    std::string lcmUrl;

    const char* optstring = "fic:shm:vu:qa";
    int c;
    struct option long_opts[] = {
        { "split-mb", required_argument, 0, 'b' },
        { "channel", required_argument, 0, 'c' },
        { "force", no_argument, 0, 'f' },
        { "increment", required_argument, 0, 'i' },
        { "lcm-url", required_argument, 0, 'l' },
        { "max-unwritten-mb", required_argument, 0, 'm' },
        { "strftime", required_argument, 0, 's' },
        { "quiet", no_argument, 0, 'q' },
        { "append", no_argument, 0, 'a' },
        { "invert-channels", no_argument, 0, 'v' },
        { "flush-interval", required_argument, 0,'u'},
        { 0, 0, 0, 0 }
    };

    while ((c = getopt_long(argc, argv, optstring, long_opts, 0)) >= 0) {
        switch (c) {
            case 'b':
                autoSplitMB = strtod(optarg, nullptr);
                if(autoSplitMB <= 0) {
                    usage();
                    return 1;
                }
                break;
            case 'f':
                forceOverwrite = true;
                break;
            case 'c':
                chanRegex = optarg;
                break;
            case 'i':
                autoIncrement = true;
                break;
            case 's':
                useStrftime = true;
                break;
            case 'l':
                lcmUrl = optarg;
                break;
            case 'q':
                quiet = true;
                break;
            case 'v':
                invertChannels = true;
                break;
            case 'm':
                maxWriteQueueSizeMB = strtod(optarg, nullptr);
                if(maxWriteQueueSizeMB <= 0) {
                    usage();
                    return 1;
                }
                break;
            case 'u':
              fflushIntervalMicrosecond = atol(optarg);
              if(fflushIntervalMicrosecond <= 0) {
                  usage();
                  return 1;
              }
              break;
            case 'a':
              append = true;
              break;
            case 'h':
            default:
                usage();
                return 1;
        };
    }

    std::string outputFilename;
    if (optind == argc) {
        outputFilename = "lcmlog-%Y-%m-%d";
        autoIncrement = 1;
        useStrftime = 1;
    } else if (optind == argc - 1) {
        outputFilename = argv[optind];
    } else if (optind < argc-1) {
        usage();
        return 1;
    }

    if(autoSplitMB > 0 && !autoIncrement) {
        fprintf(stderr, "ERROR.  --split-mb requires --increment \n");
        return 1;
    }

    if (forceOverwrite && append) {
        fprintf(stderr, "ERROR.  --force-overwrite and --append can't both be used\n");
        return 1;
    }


    cvm::sensor::logger::Logger logger(lcmUrl,          outputFilename,
                                       autoSplitMB,     forceOverwrite,
                                       autoIncrement,   useStrftime,
                                       chanRegex,       maxWriteQueueSizeMB,
                                       invertChannels,  fflushIntervalMicrosecond,
                                       quiet,           append
                                       );


    logger.loop();

    return 0;
}

