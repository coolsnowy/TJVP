/**
 * @file PushHMIConfig.h
 * @brief the config file of PushHMI
 */

#ifndef _CVM_APPLICATION_PUSHHMI_PUSHHMICONFIG_H_
#define _CVM_APPLICATION_PUSHHMI_PUSHHMICONFIG_H_

#define CVM_APPLICATION_PUSHHMI_CONFIG_FILE  "/etc/cvm/cvm-pushhmi.conf"

#include <string>

namespace cvm {

namespace application{

namespace pushhmi {

struct PushHMIConfig
{
    PushHMIConfig(int argc, char **argv, const std::string& configFile);

    static void printHelp();
    void printConfig();


    bool debug;
    std::string logPath;
};


enum EventType{
    DEFAULTTYPE = 0,
    CARTYPE = 1,
    ROADTYPE = 2,
    TAGTYPE = 3,
    PAYTYPE = 4
};



}

}

}

#endif
