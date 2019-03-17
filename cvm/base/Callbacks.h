/**
  * @file Callbacks.h
  * @brief 回调函数的定义
  */
#ifndef _CVM_BASE_CALLBACKS_H_
#define _CVM_BASE_CALLBACKS_H_

#include <functional>

namespace cvm
{
namespace base
{

typedef std::function<void()> TimerCallback;

}

}
#endif // _CVM_BASE_CALLBACKS_H_
