#include <functional>
#include <map>

#include <stdio.h>
#include <unistd.h>

#include <cvm/base/FileLogger.h>
#include <cvm/base/Logging.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/ThreadId.h>

using namespace cvm;
using namespace cvm::base;

int cnt = 0;
int timerNum = 0;
EventLoop* g_loop;
std::map<int, Timestamp> g_time;

void printTid()
{
    LDEBUG << "pid = " << getpid();
    LDEBUG << "now " << Timestamp::now().toString();
}

void print(const char* msg, int timerNum)
{
    if (g_time.find(timerNum) == g_time.end()) {
        g_time[timerNum] = Timestamp::now();
        LWARN << msg << " first timeout";
    }else {
        LWARN << msg << " " << differTime(Timestamp::now(), g_time[timerNum]) / 1000
                 << "ms from last";
        g_time[timerNum] = Timestamp::now();
    }
}

void cancel(TimerId timer)
{
    g_loop->cancel(timer);
    LDEBUG << "cancelled at " << Timestamp::now().toString();
}

int main()
{
    Logging::setLogLevel(Logging::LogLevel::Debug);

    printTid();
    {
        EventLoop loop;
        g_loop = &loop;

        loop.runEvery(200, std::bind(print, "every200ms", timerNum++));
        loop.runEvery(1600, std::bind(print, "every1.6s", timerNum++));
        loop.runEvery(1500, std::bind(print, "every1.5s", timerNum++));
        loop.runEvery(1400, std::bind(print, "every1.4s", timerNum++));
        TimerId t45 = loop.runAfter(4500, std::bind(print, "once4.5s", timerNum++));
        loop.runAfter(4200, std::bind(cancel, t45));
        loop.runAfter(4800, std::bind(cancel, t45));
        loop.runEvery(2000, std::bind(print, "every2s", timerNum++));
        TimerId t3 = loop.runEvery(3000, std::bind(print, "every3s", timerNum++));

        loop.runAfter(20000, std::bind(cancel, t3));

        loop.loop();
    }
    return 0;
}
