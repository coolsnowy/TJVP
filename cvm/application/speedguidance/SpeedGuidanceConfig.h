/**
 * @file SpeedGuidanceConfig.h
 * @brief the config file of SpeedGuidance
 */

#ifndef _CVM_APPLICATION_SPEEDGUIDANCE_SPEEDGUIDANCECONFIG_H_
#define _CVM_APPLICATION_SPEEDGUIDANCE_SPEEDGUIDANCECONFIG_H_

#include <string>

#define CVM_APPLICATION_SPEEDGUIDANCE_CONFIG_FILE "/etc/cvm/cvm-speedguidance.conf"

namespace cvm {

namespace application {

namespace speedguidance {

struct SpeedGuidanceConfig
{
    SpeedGuidanceConfig(int argc, char **argv, const std::string& configFile);

    static void printHelp();
    void printConfig();


    bool debug;
    std::string logPath;
};



/**
 * @ brief The VectorPP struct: vector in RCS: A -> B
 */
struct VectorPP{
    double x;
    double y;
};

enum SignalPhase{
    SIGNAL_DEFAULT = 0,
    GREENLIGHT = 1,
    YELLOWLIGHT = 2,
    REDLIGHT  = 4
};

}

}

}

#endif

