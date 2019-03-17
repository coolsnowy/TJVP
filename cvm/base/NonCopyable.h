/**
 * @file NonCopyable.h
 * @brief NonCopyable类的定义
 */

#ifndef _CVM_BASE_NONCOPYABLE_H_
#define _CVM_BASE_NONCOPYABLE_H_

namespace cvm
{
namespace base
{
/**
 * @class NonCopyable
 * @brief 提供不可赋值构造、不可拷贝的值语义
 */
class NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable& ) = delete;
    NonCopyable& operator=(const NonCopyable &) = delete;
};

}

}

#endif // _CVM_BASE_NONCOPYABLE_H_
