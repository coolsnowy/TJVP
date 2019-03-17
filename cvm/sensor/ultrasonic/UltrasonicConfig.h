#ifndef _CVM_SENSOR_ULTRASONIC_ULTRASONICCONFIG_H_
#define _CVM_SENSOR_ULTRASONIC_ULTRASONICCONFIG_H_

#include <string>

#define CVM_SENSOR_ULTRASONIC_CONFIG_FILE "/etc/cvm/cvm-ultrasonic.conf"

namespace cvm
{

namespace sensor
{

namespace ultrasonic
{

struct UltrasonicConfig
{
    // Parse in constructor
    UltrasonicConfig(int argc, char** argv, const std::string& configFile);

    void printConfig();
    static void printHelp();

    // Config Data member
};

}

}

}

#endif // _CVM_SENSOR_ULTRASONIC_ULTRASONICCONFIG_H_
