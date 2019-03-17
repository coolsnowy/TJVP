/**
 * @file EventLoop.h
 * @brief CountDownLatch类的定义
 *
 */

#ifndef _CVM_BASE_COUNTDOWNLATCH_H_
#define _CVM_BASE_COUNTDOWNLATCH_H_

#include <mutex>
#include <condition_variable>

#include <cvm/base/NonCopyable.h>

namespace cvm
{

namespace base
{

/**
  * @class CountDownLatch
  * @brief 倒计时
  *
  * 多线程同步的工具，只有在计数减少到0的时候wait函数才会继续
  */
class CountDownLatch : public NonCopyable
{
public:
    /**
     * @brief CountDownLatch的构造函数
     * @param count 倒计时计数
     */
    CountDownLatch(int count);
    ~CountDownLatch();

    /**
     * @brief 阻塞线程，直到计数为0
     */
    void wait();

    /**
     * @brief 计数-1
     */
    void countDown();

    /**
     * @brief 获取当前剩余计数
     * @return 当前剩余计数
     */
    int getCount();

private:
    int _count;
    std::mutex _mutex;
    std::condition_variable _conditionVariable;
};

}

}

#endif // _CVM_BASE_COUNTDOWNLATCH_H_
