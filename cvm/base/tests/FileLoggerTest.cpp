#include <cvm/base/FileLogger.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/Logging.h>

using namespace cvm;
using namespace cvm::base;

int main()
{
    Logging::setLogLevel(Logging::LogLevel::Warn);
    FileLogger logger;
    Logging::initLogging(Logging::LogLevel::Warn,
                         [&](const char* data, int64_t size){ logger.log(data, size); },
                         [&](Timestamp now) { logger.flush(now); } );

    char buffer1[5000] = {0};
    for (int i=0; i<sizeof(buffer1)-1; i++) {
        buffer1[i] = '1';
    }

    char buffer2[3000] = {0};
    for (int i=0; i<sizeof(buffer2)-1; i++) {
        buffer2[i] = '2';
    }

    char buffer3[300] = {0};
    for (int i=0; i<sizeof(buffer3)-1; i++) {
        buffer3[i] = 'R';
    }

    Timestamp start(Timestamp::now());
    for (int i=0; i<3000; i++) {
        LDEBUG << buffer1;
    }
    Timestamp end(Timestamp::now());
    printf("Time costs %s \n", Timestamp(differTime(end, start)).toString().data());

    start = Timestamp::now();
    for (int i=0; i<3000; i++) {
        LINFO << buffer2;
    }
    end = Timestamp::now();
    printf("Time costs %s \n", Timestamp(differTime(end, start)).toString().data());

    start = Timestamp::now();
    for (int i=0; i<3000; i++) {
        LWARN << buffer3;
    }
    end = Timestamp::now();
    printf("Time costs %s \n", Timestamp(differTime(end, start)).toString().data());

    start = Timestamp::now();
    for (int i=0; i<3000; i++) {
        LERROR << buffer2;
    }
    end = Timestamp::now();
    printf("Time costs %s \n", Timestamp(differTime(end, start)).toString().data());


    LDIE << buffer3;

    return 0;
}
