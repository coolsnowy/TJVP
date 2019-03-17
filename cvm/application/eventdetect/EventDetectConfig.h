/**
 * @file EventDetectConfig.h
 * @brief the config file of event-detect
 */


#ifndef _CVM_APPLICATION_EVENTDETECT_EVENTDETECTCONFIG_H_
#define _CVM_APPLICATION_EVENTDETECT_EVENTDETECTCONFIG_H_

#define CVM_APPLICATION_EVENTDETECT_CONFIG_FILE  "/etc/cvm/cvm-eventdetect.conf"
#include <cvm/base/Logging.h>
#include <libconfig/libconfig.h++>
#include <string>
#include <iostream>

namespace cvm {

namespace application {

namespace eventdetect {

struct EventDetectConfig{

    EventDetectConfig(int argc, char **argv, const std::string& configFile);
    static void printHelp();
    void printConfig();

    bool debug;
    std::string logPath;
    double latitude;
    double longitude;
};

}

}

}
#endif
