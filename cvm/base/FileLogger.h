/**
 * @file FileLogger.h
 * @brief FileLogger类的定义
 *
 */
#ifndef _CVM_BASE_FILELOGGER_H_
#define _CVM_BASE_FILELOGGER_H_

#include <vector>
#include <memory>
#include <mutex>

#include <cvm/base/Timestamp.h>
#include <cvm/base/NonCopyable.h>

namespace cvm
{
namespace base
{

/**
  * @class FileLogger
  * @brief 日志后端
  *
  * 提供自动更换存储的文件，定时写入磁盘的功能
  */
class FileLogger : public NonCopyable
{
public:

    /**
      * @brief FileLogger的构造函数
      * @param flushIntervalSecond 如果此参数大于0，则定时写入磁盘，否则每次日志操作都写入磁盘
      * @param threadSafe 是否需要线程安全
      * @param path 日志文件的路径前缀
      * @param bufferSize 一条记录最大的字节数
      * @param rollSizeByte 如果当前存储文件的大小超过此参数，则自动更换文件存储
      * @param rollIntervalSecond 如果当前时间和上次更换文件存储的间隔大于此参数，则自动更换文件存储
      */
    FileLogger(int64_t flushIntervalSecond = 2,
               bool threadSafe = false,
               const std::string& path = "",
               int64_t bufferSize = 4096,
               int64_t rollSizeByte = 1024 * 1024 * 1024,
               int64_t rollIntervalSecond = 24 * 60 * 60);
    ~FileLogger();

    /**
     * @brief 记录数据
     * @param data 待记录的数据
     * @param size 待记录的数据的大小
     */
    void log(const char* data, int64_t size);

    /**
     * @brief 将数据从缓存区写入磁盘
     * @param now 当前的时间戳
     */
    void flush(Timestamp now);

    /**
     * @brief 返回从上次更换存储文件后当前记录的字节数
     * @return 当前记录的字节数
     */
    int64_t logSize();

private:

    void roll(Timestamp now);
    void flushWithoutLock(Timestamp now);

    static std::string logFileName(const std::string& path);

    int64_t _rollSizeByte;
    int64_t _rollIntervalSecond;
    int64_t _flushIntervalSecond;
    int64_t _bufferSize;
    const std::string _path;

    Timestamp _lastRoll;
    Timestamp _lastFlush;
    int64_t _currentLogBytesFromLastRoll;

    std::vector<char> _buffer;

    bool _threadSafe;

    class Writter;
    std::unique_ptr<Writter> _writter;
    std::unique_ptr<std::mutex> _mutex;
};

}
}


#endif // _CVM_BASE_FILELOGGER_H_
