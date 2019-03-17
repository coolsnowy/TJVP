#include <cvm/base/CountDownLatch.h>

namespace cvm
{

namespace base
{

CountDownLatch::CountDownLatch(int count)
    :_count(count)
{
}

int CountDownLatch::getCount()
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _count;
}

void CountDownLatch::countDown()
{
    std::unique_lock<std::mutex> lock(_mutex);
    if (--_count == 0) {
        _conditionVariable.notify_all();
    }
}

void CountDownLatch::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _conditionVariable.wait(lock, [=](){return _count==0;});
}

CountDownLatch::~CountDownLatch()
{
}

}
}
