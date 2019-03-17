#include <functional>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/timerfd.h>

#include <cvm/base/Utils.h>
#include <cvm/base/Logging.h>
#include <cvm/base/TimerQueue.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/TimerId.h>

namespace cvm
{

namespace base
{


class TimerQueue::Timer
{
public:
    Timer() {}
    ~Timer() { _channel->disableAll(); _channel->remove(); }

    int _fd;
    int64_t _delayMicrosecond;
    int64_t _intervalMicrosecond;
    std::shared_ptr<Channel> _channel;
    TimerCallback _callback;
};

TimerQueue::TimerQueue(EventLoop* loop)
    : _loop(loop)
{
}

TimerQueue::~TimerQueue()
{
    for (auto& timer : _timers) {
        timer.second->_channel->remove();
    }
}

TimerId TimerQueue::addTimer(const TimerCallback& cb, int64_t delayMicrosecond, int64_t intervalMicrosecond)
{
    auto timer = std::make_shared<Timer>();

    timer->_fd = createTimerfd();
    timer->_channel = std::make_shared<Channel>(_loop, timer->_fd);
    timer->_callback = cb;
    timer->_delayMicrosecond = delayMicrosecond;
    timer->_intervalMicrosecond = intervalMicrosecond;

    setTimerfd(timer->_fd, timer->_delayMicrosecond, timer->_intervalMicrosecond);
    timer->_channel->setReadCallback(std::bind(&TimerQueue::handleRead, this, timer->_fd));

    _loop->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));
    return timer->_fd;
}

void TimerQueue::cancelTimer(TimerId timerId)
{
    _loop->runInLoop(std::bind(&TimerQueue::cancelTimerInLoop, this, timerId));
}

void TimerQueue::addTimerInLoop(std::shared_ptr<Timer> timer)
{
    _loop->assertInLoopThread();
    _timers[timer->_fd] = timer;

    timer->_channel->enableReading();
}

void TimerQueue::handleRead(TimerId timerId)
{
    auto timer = _timers.find(timerId);
    assert(timer != _timers.end());

    readTimerfd(timer->second->_fd);

    if (timer->second->_callback) {
        timer->second->_callback();
    }

    // Clear one shot timer
    if (!timer->second->_intervalMicrosecond > 0) {
        _timers.erase(timer);
    }
}

void TimerQueue::cancelTimerInLoop(TimerId timerId)
{
    _loop->assertInLoopThread();

    auto timer = _timers.find(timerId);
    if (timer != _timers.end()) {
        _timers.erase(timer);
    }
}

}

}
