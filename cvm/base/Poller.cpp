#include <assert.h>
#include <errno.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Poller.h>
#include <cvm/base/Channel.h>

namespace cvm
{

namespace base
{

const int kNoListened  = 0;
const int kListened    = 1;

Poller::Poller(EventLoop* loop)
    : _loop(loop),
      _epollfd(::epoll_create1(EPOLL_CLOEXEC)),
      _events(kInitEventVectorSize)
{
    if (_epollfd < 0) {
        LDIE << "Open epollfd fails";
    }
}

Poller::~Poller()
{
    ::close(_epollfd);
}

Timestamp Poller::poll(int timeoutMilisecond, ChannelList* activeChannels)
{
    int numEvents = ::epoll_wait(_epollfd, &*_events.begin(),
                                 static_cast<int>(_events.size()), timeoutMilisecond);
    Timestamp now(Timestamp::now());
    if (numEvents > 0) {
        fillActiveChannels(numEvents, activeChannels);
        if (static_cast<size_t>(numEvents) == _events.size()) {
            _events.resize(_events.size() * 2);
        }
    }
    return now;
}

void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const
{
    assert(static_cast<size_t>(numEvents) <= _events.size());

    for (int i = 0; i < numEvents; ++i) {
        Channel* channel = static_cast<Channel*>(_events[i].data.ptr);
        channel->setTevents(_events[i].events);
        activeChannels->push_back(channel);
    }
}

void Poller::insertChannel(Channel* channel)
{
    const int fd = channel->getFd();
    assert(_channels.find(fd) == _channels.end());

    _channels[fd] = channel;
    channel->setInternalFlag(kNoListened);
}


void Poller::updateChannel(Channel* channel)
{
    const int internalFlag = channel->getInternalFlag();
    const int fd = channel->getFd();

    assert(_channels.find(fd) != _channels.end());
    assert(_channels[fd] = channel);

    if (internalFlag == kNoListened) {
        if (!channel->isNoneEvent()) {
            channel->setInternalFlag(kListened);
            update(EPOLL_CTL_ADD, channel);
        }
    }else {
        if (!channel->isNoneEvent()) {
            update(EPOLL_CTL_MOD, channel);
        }else {
            channel->setInternalFlag(kNoListened);
            update(EPOLL_CTL_DEL, channel);
        }
    }

}

void Poller::removeChannel(Channel* channel)
{
    const int fd = channel->getFd();
    assert(_channels.find(fd) != _channels.end());
    assert(_channels[fd] == channel);
    assert(channel->isNoneEvent());
    int internalFlag = channel->getInternalFlag();
    assert(internalFlag == kNoListened);
    size_t n = _channels.erase(fd);
    assert(n == 1);

    update(EPOLL_CTL_DEL, channel);

    channel->setInternalFlag(kNoListened);
}

void Poller::update(int operation, Channel* channel)
{
    struct epoll_event event;
    bzero(&event, sizeof(event));
    event.events = channel->getEvents();
    event.data.ptr = channel;
    const int fd = channel->getFd();
    if (::epoll_ctl(_epollfd, operation, fd, &event) < 0) {
        LDIE << "epoll_ctl error";
    }
}

bool Poller::hasChannel(Channel* channel) const
{
    _loop->assertInLoopThread();
    const auto it = _channels.find(channel->getFd());
    return it != _channels.end() && it->second == channel;
}

}

}
