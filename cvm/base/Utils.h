/**
 * @file Utils.h
 * @brief 一些实用的函数
 *
 */

#ifndef _CVM_BASE_UTILS_H_
#define _CVM_BASE_UTILS_H_

#include <unistd.h>
#include <stdint.h>

namespace cvm
{

namespace base
{

int createTimerfd();
int createEventfd();
void readTimerfd(int timerfd);
void setTimerfd(int timerfd, int64_t delayMicrosecond, int64_t intervalMicrosecond);
size_t hashCurrentThreadId();

}

}

#endif // _CVM_BASE_UTILS_H_
