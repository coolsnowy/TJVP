#include <iostream>

#include <cvm/base/Logging.h>
#include <cvm/sensor/millimeterwave/MillimeterWaveConfig.h>

namespace cvm
{

namespace sensor
{

namespace millimeterwave
{

MillimeterWaveConfig::MillimeterWaveConfig(int argc, char** argv, const std::string& configFile)
{
    if (argc < 2) {
        DIE("Millimeter Config parse error");
    }

}

void MillimeterWaveConfig::printConfig()
{
}

void MillimeterWaveConfig::printHelp()
{
}

}

}
}
