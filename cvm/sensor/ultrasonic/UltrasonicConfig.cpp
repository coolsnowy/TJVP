#include <iostream>

#include <cvm/base/Logging.h>
#include <cvm/sensor/ultrasonic/UltrasonicConfig.h>

namespace cvm
{

namespace sensor
{

namespace ultrasonic
{

UltrasonicConfig::UltrasonicConfig(int argc, char** argv, const std::string& configFile)
{
    if (argc < 2) {
        DIE("Millimeter Config parse error");
    }

}

void UltrasonicConfig::printConfig()
{
}

void UltrasonicConfig::printHelp()
{
}

}

}

}
