/**
 *
 * @file Channel.h
 * @brief Channel 类的定义
 *
 */
#ifndef _CVM_BASE_CHANNEL_H_
#define _CVM_BASE_CHANNEL_H_

#include <functional>
#include <mutex>
#include <memory>

#include <cvm/base/Timestamp.h>
#include <cvm/base/NonCopyable.h>

namespace cvm
{

namespace base
{

class EventLoop;

/**
  * @class Channel
  * @brief 设置和某个文件描述符有关的回调函数，并在事件出现时调用
  */
class Channel : public NonCopyable
{
public:
    typedef std::function<void(Timestamp)> EventCallback;

    /**
     * @brief Channel 类的构造函数
     * @param loop 监听此Channel的EventLoop
     * @param fd 受此Channel管理的文件描述符
     * @param name Channel的名称
     */
    Channel(EventLoop* loop, int fd, const std::string& name = "");
    ~Channel();

    // Just like event_data_t defined in <sys/epoll.h>
    union UserData
    {
        uint32_t u32;
        uint64_t u64;
        void*    ptr;
    };

    /**
     * @brief 设置可读事件的回调函数
     * @param cb 回调函数
     */
    void setReadCallback(const EventCallback& cb)
    { _readCallback = cb; }

    /**
     * @brief 设置可写事件的回调函数
     * @param cb 回调函数
     */
    void setWriteCallback(const EventCallback& cb)
    { _writeCallback = cb; }

    /**
     * @brief 设置关闭事件的回调函数，只在文件描述符是TCP的情况下有用
     * @param cb 回调函数
     */
    void setCloseCallback(const EventCallback& cb)
    { _closeCallback = cb; }

    /**
     * @brief 设置错误事件的回调函数
     * @param cb 回调函数
     */
    void setErrorCallback(const EventCallback& cb)
    { _errorCallback = cb; }

    /**
     * @brief 打开可读事件
     */
    void enableReading() { _events |= kReadEvent; update(); }

    /**
     * @brief 关闭可读事件
     */
    void disableReading() { _events &= ~kReadEvent; update(); }

    /**
     * @brief 打开可写事件
     */
    void enableWriting() { _events |= kWriteEvent; update(); }

    /**
     * @brief 关闭可写事件
     */
    void disableWriting() { _events &= ~kWriteEvent; update(); }

    /**
     * @brief 关闭所有事件
     */
    void disableAll() { _events = kNoneEvent; update(); }

    /**
     * @brief 将此Channel加入此EventLoop
     */
    void insert();

    /**
     * @brief 将此Channel移出EventLoop
     */
    void remove(); // remove will disableAll listening events and remove channel from eventloop

    /**
     * @brief 事件分发，并执行对应的回调函数
     * @param receiveTime 事件出现的时间戳
     */
    void handleEvent(Timestamp receiveTime);

    EventLoop* getLoop() { return _loop; }
    const std::string& getName() const { return _name; }
    int  getFd() const { return _fd; }
    int  getEvents() const { return _events; }

    // Used by Poller
    void setTevents(int tevents) { _tevents = tevents; }
    int  getTevents() const { return _tevents; }
    int  getInternalFlag() const { return _internalFlag; }
    void setInternalFlag(int internalFlag) { _internalFlag = internalFlag; }

    UserData getUserData() { return _userData; }
    void setUserData(UserData userData) { _userData = userData; }

//    // std::any in c++17
//    std::any& getUserData() { return _userData; }
//    void setUserData(const std::any& userData) { _userData = userData; }

    bool isNoneEvent() const { return _events == kNoneEvent; }
    bool isWriting() const { return _events & kWriteEvent; }
    bool isReading() const { return _events & kReadEvent; }

private:

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;


    void update();

    EventLoop* _loop;
    const std::string _name;
    const int  _fd;
    int        _internalFlag;  // Set by Poller
    int        _events;
    int        _tevents; // Triggered event
    int        _index;

    bool _eventHandling;
    bool _addedToLoop;

    UserData _userData;

//    // std::any in c++17
//    std::any _userData;

    EventCallback _readCallback;
    EventCallback _writeCallback;
    EventCallback _closeCallback;
    EventCallback _errorCallback;
};

}

}

#endif // _CVM_BASE_CHANNEL_H_
