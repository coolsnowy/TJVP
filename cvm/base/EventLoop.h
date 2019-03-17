/**
 * @file EventLoop.h
 * @brief EventLoop类的定义
 *
 */

#ifndef _CVM_BASE_EVENTLOOP_H_
#define _CVM_BASE_EVENTLOOP_H_

#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <functional>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/TimerId.h>
#include <cvm/base/Callbacks.h>

namespace cvm
{

namespace base
{

class Channel;
class Poller;
class TimerQueue;

/**
  * @class EventLoop
  * @brief 监听Channel，直到事件出现
  */

class EventLoop : public NonCopyable
{
public:
    typedef std::function<void()> Task;

    /**
     * @brief EventLoop的构造函数
     * @param name EventLoop的名字
     */
    EventLoop(const std::string& name = "");

    /**
     * @brief 析构函数，将会移除所有监听的Channel
     */
    ~EventLoop();

    /**
     * @brief 主循环函数
     */
    void loop();

    /**
     * @brief 退出循环，线程安全
     */
    void quit();

    /**
     * @brief 在此EventLoop运行任务
     *
     * 应在和EventLoop相同的线程调用这个函数
     *
     * @param cb 任务
     */
    void runInLoop(const Task& cb);

    /**
     * @brief 在此EventLoop运行任务，可以在不同的线程调用这个函数
     * @param cb 任务
     */
    void queueInLoop(const Task& cb);

    /**
     * @brief 获取当前任务队列的大小
     * @return 当前任务队列的大小
     */
    size_t queueSize() const;

    /**
     * @brief 获取轮询返回的时间戳
     * @return 轮询返回的时间戳
     */
    Timestamp pollReturnTime() const { return _pollReturnTime; }

    /**
     * @brief 获取EventLoop的名称
     * @return EventLoop的名称
     */
    const std::string& name() { return _name; }

    /**
     * @brief 获取当前线程对应的EventLoop的指针
     * @return 当前线程对应的EventLoop的指针
     */
    static EventLoop* getEventLoopOfCurrentThread();

    /**
     * @brief 在指定的时间点执行指定的函数
     * @param time 时间点
     * @param cb 将要执行的回调函数
     * @return 定时器id
     */
    TimerId runAt(const Timestamp& time, const TimerCallback& cb);

    /**
     * @brief 在指定的间隔后执行指定的函数，只执行一次
     * @param delayMiliseconds 时间间隔，以毫秒为单位
     * @param cb 将要执行的回调函数
     * @return 定时器id
     */
    TimerId runAfter(int64_t delayMiliseconds, const TimerCallback& cb);

    /**
     * @brief 周期性的执行指定的函数
     * @param intervalMiliseconds 周期，以毫秒为单位
     * @param cb 将要执行的回调函数
     * @return 定时器id
     */
    TimerId runEvery(int64_t intervalMiliseconds, const TimerCallback& cb);

    /**
     * @brief 根据给定的定时器id取消定时器
     * @param timerId 定时器id
     */
    void cancel(TimerId timerId);

    /**
     * @brief 唤醒此EventLoop所处的线程
     */
    void wakeup();

    /**
     * @brief 插入给定的Channel
     * @param channel 待插入的channel
     */
    void insertChannel(Channel* channel);

    /**
     * @brief 更新给定的Channel
     * @param channel 待更新的channel
     */
    void updateChannel(Channel* channel);

    /**
     * @brief 移除给定的Channel
     * @param channel 待移除的channel
     */
    void removeChannel(Channel* channel);

    /**
     * @brief 判断给定的channel是否受此EventLoop监听
     * @param channel 待判断的channel
     * @return 如果在就返回true，否则false
     */
    bool hasChannel(Channel* channel);

    /**
     * @brief 如果当前线程不是EventLoop对应的线程，就调用abort终止进程
     */
    void assertInLoopThread()
    {
        if (!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }

    /**
     * @brief 判断当前线程是否和EventLoop对应的线程相同
     * @return 相同则返回true，否则false
     */
    bool isInLoopThread() const { return _threadId == std::this_thread::get_id(); }

    bool eventHandling() const { return _eventHandling; }

private:

    void abortNotInLoopThread();
    void handleRead();
    void doPendingTasks();

    typedef std::vector<Channel*> ChannelList;

    // Atomic ?
    bool _looping;
    bool _quit;
    bool _eventHandling;
    bool _callingPendingTasks;

    const std::thread::id _threadId;
    const size_t _hashedThreadId;

    Timestamp _pollReturnTime;
    std::unique_ptr<Poller> _poller;
    std::unique_ptr<TimerQueue> _timerQueue;

    int _wakeupFd;
    std::unique_ptr<Channel> _wakeupChannel;

    ChannelList _activeChannels;
    Channel* _currentActiveChannel;

    mutable std::mutex _mutex;
    std::vector<Task> _pendingTasks; // Guarded by _mutex

    const std::string _name;

    static const int kPollTimeMilisecond;
};

}

}
#endif // _CVM_BASE_EVENTLOOP_H_
