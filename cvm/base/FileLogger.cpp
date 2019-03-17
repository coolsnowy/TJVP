#include <iostream>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <cvm/base/Logging.h>
#include <cvm/base/Utils.h>
#include <cvm/base/FileLogger.h>

namespace cvm
{

namespace base
{

class FileLogger::Writter : public NonCopyable
{
public:
    Writter(const char* path)
    {
        _fd = ::open(path, O_WRONLY | O_CREAT | O_NONBLOCK | O_CLOEXEC | O_APPEND, 0664);
        if (_fd < 0) {
            DIE("Open file fails");
        }
    }

    ~Writter()
    {
        ::close(_fd);
    }

    int flush(const char* data, int size)
    {
        /*
          See man 2 write :
            On  Linux,  write()  (and  similar  system calls) will transfer at most
            0x7ffff000 (2,147,479,552) bytes, returning the number of  bytes  actu‐
            ally transferred.  (This is true on both 32-bit and 64-bit systems.)

          And atomic is guaranteed by write if fd is opened with O_APPEND
        */
        int retval = ::write(_fd, data, size);

        if (retval < 0) {
            DIE("Write fails");
        }

        ::fsync(_fd);

        return retval;
    }

private:
    int _fd;
};

FileLogger::FileLogger(int64_t flushIntervalSecond,
                       bool threadSafe,
                       const std::string& path,
                       int64_t bufferSize,
                       int64_t rollSizeByte,
                       int64_t rollIntervalSecond)
    : _rollSizeByte(rollSizeByte),
      _bufferSize(bufferSize),
      _rollIntervalSecond(rollIntervalSecond),
      _path(path),
      _lastRoll(Timestamp::now()),
      _writter(new Writter(logFileName(path).data())),
      _lastFlush(Timestamp::now()),
      _flushIntervalSecond(flushIntervalSecond),
      _currentLogBytesFromLastRoll(0),
      _threadSafe(threadSafe)
{
    if (threadSafe) {
        _mutex.reset(new std::mutex);
    }

    if (_flushIntervalSecond > 0) {
        _buffer.reserve(_bufferSize);
    }
}

FileLogger::~FileLogger()
{
    flush(Timestamp::now());
}

void FileLogger::roll(Timestamp now)
{
    int64_t fromLastRollSecond = differTime(now, _lastRoll) / (1000 * 1000);
    if ((fromLastRollSecond >= _rollIntervalSecond) ||
            (_currentLogBytesFromLastRoll >= _rollSizeByte)) {
        _writter.reset(new Writter(logFileName(_path).data()));
        _lastRoll = now;
        _currentLogBytesFromLastRoll = 0;
    }
}

void FileLogger::log(const char* data, int64_t size)
{
    Timestamp now(Timestamp::now());

    // In some cases, a log line is longer than _buffer's max capacity
    // , then just discard it.
    if (size > _bufferSize) {
        return ;
    }

    // Keep critical section here as short as we can, since it affects performance a lot.
    std::unique_lock<std::mutex> lock;
    if (_threadSafe == true) {
        std::unique_lock<std::mutex> lk(*_mutex);
        lock.swap(lk);
    }

    roll(now);
    if (_flushIntervalSecond == 0) {
        // Directly flush to disk
        _currentLogBytesFromLastRoll += _writter->flush(data, size);
    }else {
        int64_t fromLastFlushSecond = differTime(now, _lastFlush) / (1000 * 1000);
        if ((fromLastFlushSecond >= _flushIntervalSecond) ||
                ((_bufferSize - _buffer.size()) < size)) {
            flushWithoutLock(now);
        }

        // In most case, critical section just contains a "data copy"
        std::copy(data, data + size, std::back_inserter(_buffer));
    }
}

void FileLogger::flush(Timestamp now)
{
    std::unique_lock<std::mutex> lock;
    if (_threadSafe == true) {
        std::unique_lock<std::mutex> lk(*_mutex);
        lock.swap(lk);
    }
    flushWithoutLock(now);
}

void FileLogger::flushWithoutLock(Timestamp now)
{
    if (_flushIntervalSecond > 0) {
        _currentLogBytesFromLastRoll += _writter->flush(_buffer.data(), _buffer.size());
        _buffer.clear();
        _lastFlush = now;
    }
}


int64_t FileLogger::logSize()
{
    std::unique_lock<std::mutex> lock;
    if (_threadSafe == true) {
        std::unique_lock<std::mutex> lk(*_mutex);
        lock.swap(lk);
    }
    return _currentLogBytesFromLastRoll;
}

std::string FileLogger::logFileName(const std::string& path)
{    
    char buffer[1024] = {0};
    if (::readlink("/proc/self/exe", buffer, sizeof(buffer)) < 0) {
        DIE("Get process name");
    }

    const char* processName = strrchr(buffer, '/');
    ++processName;
    const std::string processNameString(processName);
    std::string file = processNameString + ".log." + Timestamp::now().toString(false);

    if (path.empty()) {
        return file;
    }else {
        if (path[path.length()-1] == '/') {
            return path + file;
        }else {
            return path + "/" + file;
        }
    }
}

}

}
