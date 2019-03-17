#include <sstream>

#include <assert.h>
#include <sys/epoll.h>

#include <cvm/base/Logging.h>
#include <cvm/base/Channel.h>
#include <cvm/base/Utils.h>
#include <cvm/base/EventLoop.h>

namespace cvm
{

namespace base
{

namespace internal
{

std::string defaultChannelName(int num)
{
    std::ostringstream oss;
    oss << num;
    return "Channel" + oss.str();
}

}

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd, const std::string& name)
    : _loop(loop),
      _fd(fd),
      _events(0),
      _name(name.empty() ? internal::defaultChannelName(fd) : name),
      _tevents(0),
      _addedToLoop(false),
      _eventHandling(false)
{
    insert();
}

Channel::~Channel()
{
    assert(!_addedToLoop);
    assert(!_loop->hasChannel(this));
}

void Channel::insert()
{
    assert(_addedToLoop == false);
    _loop->insertChannel(this);
    _addedToLoop = true;
}

void Channel::update()
{
    assert(_addedToLoop == true);
    _loop->updateChannel(this);
}

void Channel::remove()
{
    assert(_addedToLoop == true);
    disableAll();
    assert(isNoneEvent());
    _loop->removeChannel(this);
    _addedToLoop = false;
}

void Channel::handleEvent(Timestamp receiveTime)
{
    _eventHandling = true;
    if ((_tevents & EPOLLHUP) && !(_tevents & EPOLLIN)) {
        if (_closeCallback) {
            _closeCallback(receiveTime);
        }
    }

    if (_tevents & (EPOLLERR)) {
        if (_errorCallback) {
            _errorCallback(receiveTime);
        }
    }
    if (_tevents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        if (_readCallback) {
            _readCallback(receiveTime);
        }
    }
    if (_tevents & EPOLLOUT) {
        if (_writeCallback) {
            _writeCallback(receiveTime);
        }
    }
    _eventHandling = false;
}


}

}
