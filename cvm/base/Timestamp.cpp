#include <string>

#include <inttypes.h>
#include <sys/time.h>
#include <stdio.h>

#include <cvm/base/TimerId.h>
#include <cvm/base/Timestamp.h>

namespace cvm
{

namespace base
{

std::string Timestamp::toString(bool showMicroseconds) const
{
    char buf[32] = {0};
    int64_t seconds = _microSecondsSinceEpoch / kMicrosecondsPerSecond;
    int64_t microseconds = _microSecondsSinceEpoch % kMicrosecondsPerSecond;
    if (showMicroseconds) {
        snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
    }else {
        snprintf(buf, sizeof(buf)-1, "%" PRId64 "", seconds);
    }
    return buf;
}

std::string Timestamp::toFormattedString(bool showMicroseconds) const
{
    char buf[32] = {0};
    time_t seconds = static_cast<time_t>(_microSecondsSinceEpoch / kMicrosecondsPerSecond);
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);

    if (showMicroseconds) {
        int microseconds = static_cast<int>(_microSecondsSinceEpoch % kMicrosecondsPerSecond);
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                 microseconds);
    }else {
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;
}

Timestamp Timestamp::now()
{
    struct timeval tv;
    ::gettimeofday(&tv, nullptr);
    int64_t seconds = tv.tv_sec;
    return Timestamp(seconds * kMicrosecondsPerSecond + tv.tv_usec);
}

}

}
