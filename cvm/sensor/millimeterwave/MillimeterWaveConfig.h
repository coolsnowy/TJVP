#ifndef _CVM_SENSOR_MILLIMETERWAVE_MILLIMETERWAVECONFIG_H_
#define _CVM_SENSOR_MILLIMETERWAVE_MILLIMETERWAVECONFIG_H_

#include <string>

#define CVM_SENSOR_MILLIMETERWAVE_CONFIG_FILE "/etc/cvm/cvm-millimeterwave.conf"

namespace cvm
{

namespace sensor
{

namespace millimeterwave
{

struct MillimeterWaveConfig
{
    // Parse in constructor
    MillimeterWaveConfig(int argc, char** argv, const std::string& configFile);

    void printConfig();
    static void printHelp();

    // Config Data member
};

}

}

}

#endif // _CVM_SENSOR_MILLIMETERWAVE_MILLIMETERWAVECONFIG_H_
