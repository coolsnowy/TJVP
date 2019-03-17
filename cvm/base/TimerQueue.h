/**
 * @file TimerQueue.h
 * @brief TimerQueue类的定义
 *
 */

#ifndef _CVM_BASE_TIMERQUEUE_H_
#define _CVM_BASE_TIMERQUEUE_H_

#include <memory>
#include <set>
#include <map>
#include <vector>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/Callbacks.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/Channel.h>
#include <cvm/base/TimerId.h>

namespace cvm
{

namespace base
{

class EventLoop;

/**
  * @class TimerQueue
  * @brief 使用Timerfd实现定时器，一个定时器对应一个Timerfd
  */
class TimerQueue : public NonCopyable
{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();

    /**
     * @brief 添加定时器
     * @param cb 回调函数
     * @param delayMicrosecond 首次调用回调函数的间隔
     * @param intervalMicrosecond 周期调用回调函数的间隔
     * @return 定时器id
     */
    TimerId addTimer(const TimerCallback& cb, int64_t delayMicrosecond, int64_t intervalMicrosecond);

    /**
     * @brief 取消定时器
     * @param timerId 待取消定时器的id
     */
    void cancelTimer(TimerId timerId);

private:

    class Timer;

    void handleRead(TimerId timerId);
    void addTimerInLoop(std::shared_ptr<Timer> timer);
    void cancelTimerInLoop(TimerId timerId);

    typedef std::map<TimerId, std::shared_ptr<Timer>> TimerMap;
    TimerMap _timers;
    EventLoop* _loop;
};

}

}
#endif  // _CVM_BASE_TIMERQUEUE_H_
