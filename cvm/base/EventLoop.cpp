#include <sstream>

#include <signal.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <assert.h>

#include <cvm/base/Utils.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Poller.h>
#include <cvm/base/TimerQueue.h>
#include <cvm/base/EventLoop.h>

namespace cvm
{

namespace base
{

namespace internal
{

std::string defaultEventLoopName(void* ptr)
{
    std::ostringstream oss;
    oss << reinterpret_cast<uint64_t>(ptr);
    return "EventLoop" + oss.str();
}

}

thread_local EventLoop* t_loopInThisThread = nullptr;

const int EventLoop::kPollTimeMilisecond = 10000;

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}

EventLoop::EventLoop(const std::string& name)
    : _looping(false), _quit(false), _eventHandling(false), _callingPendingTasks(false),
      _threadId(std::this_thread::get_id()),
      _hashedThreadId(hashCurrentThreadId()),
      _name(name.empty() ? internal::defaultEventLoopName(this) : name),
      _currentActiveChannel(nullptr), _poller(new Poller(this)),
      _timerQueue(new TimerQueue(this)), _wakeupFd(createEventfd()),
      _wakeupChannel(new Channel(this, _wakeupFd))
{
    LDEBUG << "EventLoop " << this << " created in thread " << _hashedThreadId;
    if (t_loopInThisThread) {
        LDIE << "Another EventLoop " << t_loopInThisThread
                  << "already exists in this thread " << _hashedThreadId;
    }else {
        t_loopInThisThread = this;
    }

    _wakeupChannel->setReadCallback(std::bind(&EventLoop::handleRead, this));
    _wakeupChannel->enableReading();
}

EventLoop::~EventLoop()
{
    LDEBUG << "EventLoop " << this << " of thread "
              << _hashedThreadId << " destructs in thread "
              << hashCurrentThreadId();
    _wakeupChannel->remove();
    ::close(_wakeupFd);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    assert(!_looping);
    assertInLoopThread();

    if (_quit == true) {
        LWARN << "quit() is called before loop()";
        return ;
    }

    _quit    = false;
    _looping = true;

    LDEBUG << "EventLoop " << name() << " start";

    while (!_quit) {
        _activeChannels.clear();
        _pollReturnTime = _poller->poll(kPollTimeMilisecond, &_activeChannels);

        // TODO sort channel by priority
        _eventHandling = true;
        for(auto& activeChannel : _activeChannels) {
            _currentActiveChannel = activeChannel;
            _currentActiveChannel->handleEvent(_pollReturnTime);
        }
        _currentActiveChannel = nullptr;
        _eventHandling = false;
        doPendingTasks();
    }

    LDEBUG << "EventLoop " << name() << " stop";
    _looping = false;
}

void EventLoop::quit()
{
    _quit = true;

    // There is a chance that loop() just executes while(!_quit) and exits,
    // then EventLoop destructs, then we are accessing an invalid object.
    // Can be fixed using _mutex in both places.

    if (!isInLoopThread()) {
        wakeup();
    }
}

void EventLoop::runInLoop(const Task& cb)
{
    if (isInLoopThread()) {
        cb();
    }else {
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(const Task& cb)
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _pendingTasks.push_back(cb);
    }

    if (!isInLoopThread() || _callingPendingTasks) {
        wakeup();
    }
}

size_t EventLoop::queueSize() const
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _pendingTasks.size();
}

TimerId EventLoop::runAt(const Timestamp& time, const TimerCallback& cb)
{
    int64_t delayMilisecond = differTime(time, Timestamp::now()) / 1000;
    return runAfter(delayMilisecond, cb);
}

TimerId EventLoop::runAfter(int64_t delayMiliseconds, const TimerCallback& cb)
{
    return _timerQueue->addTimer(cb, delayMiliseconds * 1000, 0);
}

TimerId EventLoop::runEvery(int64_t intervalMiliseconds, const TimerCallback& cb)
{
    return _timerQueue->addTimer(cb, intervalMiliseconds * 1000, intervalMiliseconds * 1000);
}

void EventLoop::cancel(TimerId timerId)
{
    return _timerQueue->cancelTimer(timerId);
}

void EventLoop::insertChannel(Channel* channel)
{
    assert(channel->getLoop() == this);
    assertInLoopThread();
    _poller->insertChannel(channel);
}

void EventLoop::updateChannel(Channel* channel)
{
    assert(channel->getLoop() == this);
    assertInLoopThread();
    _poller->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel)
{
    assert(channel->getLoop() == this);
    assertInLoopThread();
    if (_eventHandling) {
        //assert(_currentActiveChannel == channel ||
        //       std::find(_activeChannels.begin(), _activeChannels.end(), channel) == _activeChannels.end());
    }
    _poller->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel)
{
    assert(channel->getLoop() == this);
    assertInLoopThread();
    return _poller->hasChannel(channel);
}

void EventLoop::abortNotInLoopThread()
{
    LDIE << "EventLoop " << name()
              << " was created in threadId_ = " << _threadId
              << ", current thread id = " << hashCurrentThreadId();
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = ::write(_wakeupFd, &one, sizeof(one));
    if (n != sizeof(one)) {
        LERROR << "writes " << n << " bytes instead of 8";
    }
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = ::read(_wakeupFd, &one, sizeof (one));
    if (n != sizeof(one)) {
        LERROR << "reads " << n << " bytes instead of 8";
    }
}

void EventLoop::doPendingTasks()
{
    std::vector<Task> tasks;
    _callingPendingTasks = true;

    {
        std::unique_lock<std::mutex> lock(_mutex);
        tasks.swap(_pendingTasks);
    }

    for (auto& task : tasks) {
        task();
    }

    _callingPendingTasks = false;
}


}

}
