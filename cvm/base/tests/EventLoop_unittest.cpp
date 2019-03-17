#include <functional>
#include <thread>

#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include <cvm/base/EventLoop.h>

using namespace cvm;
using namespace cvm::base;

EventLoop* g_loop;

void callback(EventLoop* loop)
{
    printf("callback(): pid = %d, tid = %d, EventLoop = %s\n",
           getpid(), tid(), loop->name().data());
    EventLoop anotherLoop("another loop");
}

void threadFunc()
{
    printf("threadFunc(): pid = %d, tid = %d\n", getpid(), tid());

    assert(EventLoop::getEventLoopOfCurrentThread() == nullptr);
    EventLoop loop("thread loop");
    assert(EventLoop::getEventLoopOfCurrentThread() == &loop);
    loop.runAfter(1000, std::bind(callback, &loop));
    loop.loop();
}

int main()
{
    printf("main(): pid = %d, tid = %d\n", getpid(), tid());

    assert(EventLoop::getEventLoopOfCurrentThread() == nullptr);
    EventLoop loop("main loop");
    assert(EventLoop::getEventLoopOfCurrentThread() == &loop);

    std::thread thread(threadFunc);

    loop.loop();
    thread.join();

    return 0;
}
