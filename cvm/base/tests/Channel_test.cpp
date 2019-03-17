#include <functional>
#include <map>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <inttypes.h>

#include <cvm/base/Logging.h>
#include <cvm/base/Channel.h>
#include <cvm/base/Utils.h>
#include <cvm/base/EventLoop.h>


using namespace cvm;
using namespace cvm::base;

void print(const char* msg)
{
    static std::map<const char*, Timestamp> lasts;
    Timestamp& last = lasts[msg];
    Timestamp now = Timestamp::now();
    printf("%s %s delay %" PRIu64 "\n", now.toString().c_str(),
           msg, differTime(now, last));
    last = now;
}

namespace cvm
{
namespace base
{
namespace internal
{

int createTimerfd();
void readTimerfd(int timerfd);

}
}
}

// Use relative time, immunized to wall clock changes.
class PeriodicTimer
{
public:
    PeriodicTimer(EventLoop* loop, int64_t intervalMs, const TimerCallback& cb)
        : loop_(loop),
          timerfd_(cvm::base::createTimerfd()),
          timerfdChannel_(loop, timerfd_),
          interval_(intervalMs),
          cb_(cb)
    {
        timerfdChannel_.setReadCallback(
                    std::bind(&PeriodicTimer::handleRead, this));
        timerfdChannel_.enableReading();
    }

    void start()
    {
        struct itimerspec spec;
        bzero(&spec, sizeof spec);
        spec.it_interval = toTimeSpec(interval_);
        spec.it_value = spec.it_interval;
        int ret = ::timerfd_settime(timerfd_, 0, &spec, nullptr);
        if (ret) {
            LERROR << "timerfd_settime()";
        }
    }

    ~PeriodicTimer()
    {
        timerfdChannel_.disableAll();
        timerfdChannel_.remove();
        ::close(timerfd_);
    }

private:
    void handleRead()
    {
        loop_->assertInLoopThread();
        readTimerfd(timerfd_);
        if (cb_) {
            cb_();
        }
    }

    static struct timespec toTimeSpec(int64_t microseconds)
    {
        struct timespec ts;
        bzero(&ts, sizeof(ts));
        const int64_t kNanoSecondsPerSecond = 1e9;
        const int kMinInterval = 1e5;
        int64_t nanoseconds = static_cast<int64_t>(microseconds * 1000 * 1000);
        if (nanoseconds < kMinInterval)
            nanoseconds = kMinInterval;
        ts.tv_sec = static_cast<time_t>(nanoseconds / kNanoSecondsPerSecond);
        ts.tv_nsec = static_cast<long>(nanoseconds % kNanoSecondsPerSecond);
        return ts;
    }

    EventLoop* loop_;
    const int timerfd_;
    Channel timerfdChannel_;
    const double interval_; // in seconds
    TimerCallback cb_;
};

int main(int argc, char* argv[])
{
    EventLoop loop("main loop");
    PeriodicTimer timer(&loop, 1000, std::bind(print, "PeriodicTimer"));
    timer.start();
    loop.loop();

    return 0;
}

