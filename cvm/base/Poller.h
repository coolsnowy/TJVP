/**
 * @file Poller.h
 * @brief Poller类的定义
 *
 */

#ifndef _CVM_BASE_POLLER_H_
#define _CVM_BASE_POLLER_H_

#include <vector>
#include <map>

#include <cvm/base/Timestamp.h>

struct epoll_event;

namespace cvm
{
namespace base
{

class Channel;
class EventLoop;

/**
  * @class Poller
  * @brief 为EventLoop提供真正的轮询实现
  */
class Poller
{
public:
    typedef std::vector<Channel*> ChannelList;

    Poller(EventLoop* loop);
    ~Poller();

    /**
     * @brief 轮询所有channel
     * @param timeoutMilisecond 超时时间
     * @param activeChannels 将有事件发生的channel填入此channelList中
     * @return 轮询结束时的时间戳
     */
    Timestamp poll(int timeoutMilisecond, ChannelList* activeChannels);

    /**
     * @brief 插入Channel
     * @param channel 待插入的channel
     */
    void insertChannel(Channel* channel);

    /**
     * @brief 更新channel
     * @param channel 待更新的channel
     */
    void updateChannel(Channel* channel);

    /**
     * @brief 移除channel
     * @param channel 待移除的channel
     */
    void removeChannel(Channel* channel);

    /**
     * @brief 判断channel是否在此poller监听的范围中
     * @param channel 待判断的channel
     * @return 如果在就返回true，否则返回false
     */
    bool hasChannel(Channel* channel) const;

private:
    static const int kInitEventVectorSize = 32;

    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    void update(int operation, Channel* channel);

    typedef std::vector<struct epoll_event> EventVector;
    typedef std::map<int, Channel*> ChannelMap;

    EventLoop* _loop;
    int _epollfd;
    EventVector _events;
    ChannelMap  _channels;

};

}
}

#endif  // _CVM_BASE_POLLER_H_
