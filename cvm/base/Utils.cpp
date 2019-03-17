#include <sstream>
#include <thread>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>

#include <cvm/base/Logging.h>
#include <cvm/base/Utils.h>

namespace cvm
{

namespace base
{


int createEventfd()
{
    int eventfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (eventfd < 0) {
        LDIE << "Open eventfd";
    }
    return eventfd;
}

int createTimerfd()
{
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if (timerfd < 0) {
        LDIE << "Open timerfd";
    }
    return timerfd;
}

void readTimerfd(int timerfd)
{
    uint64_t howmany;
    ssize_t n = ::read(timerfd, &howmany, sizeof howmany);
    (void)n;

    // How to correct handler failure ?
}

void setTimerfd(int timerfd, int64_t delayMicrosecond, int64_t intervalMicrosecond)
{
    assert((delayMicrosecond >= 0) && (intervalMicrosecond >= 0));

    struct itimerspec newValue;
    struct itimerspec oldValue;
    bzero(&newValue, sizeof newValue);
    bzero(&oldValue, sizeof oldValue);
    newValue.it_value.tv_sec  = delayMicrosecond / (1000 * 1000);
    newValue.it_value.tv_nsec = delayMicrosecond % (1000 * 1000) * 1000;
    newValue.it_interval.tv_sec  = intervalMicrosecond / (1000 * 1000);
    newValue.it_interval.tv_nsec = intervalMicrosecond % (1000 * 1000) * 1000;
    int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
    (void)ret;

    // How to correct handler failure ?
}

size_t hashCurrentThreadId()
{
    return std::hash<std::thread::id>()(std::this_thread::get_id());
}


}

}
