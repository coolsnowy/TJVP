/**
 * @file Logging.h
 * @brief Logging类的定义
 *
 */
#ifndef _CVM_BASE_LOGGING_H_
#define _CVM_BASE_LOGGING_H_

#include <sstream>
#include <memory>
#include <functional>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <cvm/base/FileLogger.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/NonCopyable.h>


namespace cvm
{
namespace base
{

/**
  * @class Logging
  * @brief 日志前端
  */
class Logging : public NonCopyable
{
public:
    enum LogLevel
    {
        Debug,
        Info,
        Warn,
        Error,
        Die,
        LogLevelNum
    };

    /**
      * @brief Logging的构造函数
      * @param logLevel 本条记录的日志级别
      * @param file 需要日志的源文件名
      * @param func 日志操作所处的函数
      * @param line 日志操作所处的行数
      * @param verbose 是否日志冗余数据
      * @param abort 是否终止进程
      */
    Logging(LogLevel logLevel, const char* file, const char* func, int line,
            bool verbose = true, bool abort = false);
    ~Logging();

    typedef std::function<void(const char*, int64_t)> LogFunc;
    typedef std::function<void(Timestamp)> FlushFunc;

    /**
      * @brief 设置默认的日志级别
      * @param logLevel 默认的日志级别
      */
    static void setLogLevel(LogLevel logLevel)
    {
        assert(logLevel < LogLevelNum);
        s_logLevel = logLevel;
    }

    /**
      * @brief 返回默认的日志级别
      * @return 默认的日志级别
      */
    static LogLevel logLevel() { return s_logLevel; }

    /**
      * @brief 设置log后端的记录函数
      * @param logFunc log后端的记录函数
      */
    static void setLogFunc(const LogFunc& logFunc) { s_logFunc = logFunc; }

    /**
      * @brief 设置log后端的刷新函数
      * @param flushFunc log后端的刷新函数
      */
    static void setFlushFunc(const FlushFunc& flushFunc) { s_flushFunc = flushFunc; }

    static void initLogging(LogLevel logLevel, const LogFunc& logFunc,
                            const FlushFunc& flushFunc)
    {
        s_logFunc = logFunc;
        s_flushFunc = flushFunc;
        s_logLevel = logLevel;
    }

    template<typename T>
    Logging& operator<<(const T& data)
    {
        _stream << data;
        return *this;
    }

    template<typename T>
    Logging& operator<<(const T* data)
    {
        _stream << "0x" << std::hex << reinterpret_cast<int64_t>(data);
        return *this;
    }

    Logging& operator<<(const char* data)
    {
        _stream << data;
        return *this;
    }

    Logging& operator<<(char* data)
    {
        _stream << reinterpret_cast<const char*>(data);
        return *this;
    }

private:
    bool _abort;
    std::ostringstream _stream;

    static LogFunc s_logFunc;
    static FlushFunc s_flushFunc;
    static LogLevel s_logLevel;
};

}

}

#define LOG(level, verbose) \
    if (cvm::base::Logging::logLevel() <= level) \
        cvm::base::Logging((level), __FILE__, __func__, __LINE__, (verbose))

#define LDEBUG LOG(cvm::base::Logging::LogLevel::Debug, true)
#define LINFO  LOG(cvm::base::Logging::LogLevel::Info, true)
#define LWARN  cvm::base::Logging(cvm::base::Logging::LogLevel::Warn, \
                __FILE__, __func__, __LINE__, true)
#define LERROR cvm::base::Logging(cvm::base::Logging::LogLevel::Error, \
                __FILE__, __func__, __LINE__, true)
#define LDIE   cvm::base::Logging(cvm::base::Logging::LogLevel::Die, \
                __FILE__, __func__, __LINE__, true, true)

// strerror_r dosen't fill buffer passed in ?
#define DIE(format, ...) \
    { \
        char buffer[64] = {0}; \
        const char* estr = strerror_r(errno, buffer, sizeof(buffer)); \
        const char* fstr = ::strrchr(__FILE__, '/'); \
        if (fstr == nullptr) { \
            fstr = __FILE__; \
        }else { \
            ++fstr; \
        } \
        ::fprintf(stderr, "(DIE, %s, %s, %d) %s : "#format" \n", \
                  fstr, __func__, __LINE__, estr, ##__VA_ARGS__); \
        ::abort(); \
    }


#endif // _CVM_BASE_LOGGING_H_
