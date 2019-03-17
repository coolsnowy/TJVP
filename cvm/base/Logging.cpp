#include <string.h>
#include <stdio.h>

#include <cvm/base/Logging.h>

namespace cvm
{
namespace base
{

namespace internal
{

const char* logLevelString[] = { "DEBUG",
                                 "INFO",
                                 "WARN",
                                 "ERROR",
                                 "DIE" };

void defaultLogFunc(const char* data, int64_t size)
{
    fprintf(stdout, "%s", data);
    (void)size;
}

void defaultFlushFunc(Timestamp now)
{
    fflush(stdout);
}

}

Logging::LogLevel Logging::s_logLevel = Logging::LogLevel::Debug;
Logging::LogFunc Logging::s_logFunc = internal::defaultLogFunc;
Logging::FlushFunc Logging::s_flushFunc = internal::defaultFlushFunc;

Logging::Logging(Logging::LogLevel logLevel, const char* file, const char* func, int line,
                 bool verbose, bool abort)
    : _abort(abort)
{
    Timestamp now(Timestamp::now());
    _stream << "( " << internal::logLevelString[logLevel] << ", " << now.toString();

    if (verbose) {

        // Since "file" may points to a file name with full path
        // Try to trim it.
        const char* s = ::strrchr(file, '/');
        if (s != nullptr) {
            file = ++s;
        }

        _stream << ", " << file << ", " << func << ", " << line;
    }

    _stream << " ) : ";
}

Logging::~Logging()
{

    if (errno) {
        char buffer[64] = {0};
        const char* estr = strerror_r(errno, buffer, sizeof(buffer));
        _stream << " -- (errstr : " << estr << ")";
        errno = 0;
    }
    _stream << std::endl;
    s_logFunc(_stream.str().data(), _stream.str().length());
    if (_abort) {
        // Make sure logs all written to disk before abortion
        // It's helpful to debug when errors occur
        s_flushFunc(Timestamp::now());
        std::abort();
    }
}

}

}
