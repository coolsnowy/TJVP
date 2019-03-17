/**
 * @file Timestamp.h
 * @brief Timestamp类的定义
 */
#ifndef _CVM_BASE_TIMESTAMP_H_
#define _CVM_BASE_TIMESTAMP_H_

#include <string>

#include <assert.h>
#include <stdint.h>
#include <time.h>


namespace cvm
{

namespace base
{

/**
 * @class Timestamp
 * @brief 时间戳的一个实现
 */
class Timestamp
{
public:

    Timestamp(int64_t microSecondsSinceEpoch = 0)
        : _microSecondsSinceEpoch(microSecondsSinceEpoch)
    {
    }

    std::string toString(bool showMicroseconds = true) const;
    std::string toFormattedString(bool showMicroseconds = true) const;
    bool valid() const { return _microSecondsSinceEpoch > 0; }
    int64_t microSecondsSinceEpoch() const { return _microSecondsSinceEpoch; }

    time_t secondsSinceEpoch() const
    {
        return static_cast<time_t>(_microSecondsSinceEpoch / (1000 * 1000));
    }

    static Timestamp now();

    static Timestamp invalid()
    {
        return Timestamp();
    }

    static Timestamp fromUnixTime(time_t t)
    {
        return fromUnixTime(t, 0);
    }

    static Timestamp fromUnixTime(time_t t, int microseconds)
    {
        return Timestamp(static_cast<int64_t>(t) * kMicrosecondsPerSecond + microseconds);
    }

    const static int kMicrosecondsPerSecond = 1000 * 1000;

private:

    int64_t _microSecondsSinceEpoch;


};

inline bool operator==(Timestamp lhs, Timestamp rhs)
{
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline bool operator!=(Timestamp lhs, Timestamp rhs)
{
    return !(lhs == rhs);
}

inline bool operator<(Timestamp lhs, Timestamp rhs)
{
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator<=(Timestamp lhs, Timestamp rhs)
{
    return ((lhs < rhs) || (lhs == rhs));
}

inline bool operator>(Timestamp lhs, Timestamp rhs)
{
    return !(lhs <= rhs);
}

inline bool operator>=(Timestamp lhs, Timestamp rhs)
{
    return !(lhs < rhs);
}

inline int64_t differTime(Timestamp high, Timestamp low)
{
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    assert(diff >= 0);
    return diff;
}

inline Timestamp addTime(Timestamp timestamp, int64_t microSeconds)
{
    assert(microSeconds >= 0);
    return Timestamp(timestamp.microSecondsSinceEpoch() + microSeconds);
}

}

}
#endif  // _CVM_BASE_TIMESTAMP_H_
