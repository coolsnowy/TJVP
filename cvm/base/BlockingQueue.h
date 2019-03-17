/**
 * @file BlockingQueue.h
 * @brief BlockingQueue类的定义和实现
 */
#ifndef _CVM_BASE_BLOCKINGQUEUE_H_
#define _CVM_BASE_BLOCKINGQUEUE_H_

#include <functional>
#include <mutex>
#include <queue>
#include <condition_variable>

#include <cvm/base/NonCopyable.h>

namespace cvm
{

namespace base
{

/**
 * @class BlockingQueue
 * @brief 生产消费者模型的简单实现
 * @param T 数据类型
 */
template <typename T>
class BlockingQueue : public NonCopyable
{
public:
    BlockingQueue<T>() = default;
    ~BlockingQueue<T>() = default;
    
    void enqueue(const T& data);
    void enqueue(T&& data);
    T dequeueWithCopy();
    T dequeueWithMove();
    
private:
    mutable std::mutex    _queueMutex;
    std::condition_variable _queueConditionVariable;
    std::queue<T> _queue;
       
};

template<typename T>
inline void BlockingQueue<T>::enqueue(const T& data)
{
    std::unique_lock<std::mutex> lock(_queueMutex);
    _queue.push(data);
    _queueConditionVariable.notify_one();
}

template<typename T>
inline void BlockingQueue<T>::enqueue(T&& data)
{
    std::unique_lock<std::mutex> lock(_queueMutex);
    _queue.push(std::move(data));
    _queueConditionVariable.notify_one();
}

template<typename T>
inline T BlockingQueue<T>::dequeueWithCopy()
{
    std::unique_lock<std::mutex> lock(_queueMutex);
    _queueConditionVariable.wait(lock, [&](){return !_queue.empty();});
    T data = _queue.front();
    _queue.pop();
    return data;
}

template<typename T>
inline T BlockingQueue<T>::dequeueWithMove()
{
    std::unique_lock<std::mutex> lock(_queueMutex);
    _queueConditionVariable.wait(lock, [&](){return !_queue.empty();});
    T data = std::move(_queue.front());
    _queue.pop();
    return data;
}

}

}


#endif // _CVM_BASE_BLOCKINGQUEUE_H_

