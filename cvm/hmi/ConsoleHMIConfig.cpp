#include <iostream>

#include <cvm/base/Logging.h>
#include <cvm/hmi/ConsoleHMIConfig.h>

namespace cvm
{

namespace hmi
{

ConsoleHMIConfig::ConsoleHMIConfig(int argc, char** argv, const std::string& configFile)
{
    if (argc < 2) {
        DIE("HMI Config parse error");
    }

    interestedChannel = argv[1];
}

void ConsoleHMIConfig::printConfig()
{
    std::cout << "Interested Channel = " << interestedChannel << std::endl;
}

void ConsoleHMIConfig::printHelp()
{
    std::cout << "Available Channel : \n"
              << "\t GPS_PUB \n"
              << "\t CAN_PUB \n"
              << "\t CAN_CTRL \n"
              << "\t DSRC_BSM_PUB \n"
              << "\t DSRC_BSM_CTRL \n"
              << "\t DSRC_MAP_PUB \n"
              << "\t DSRC_SPAT_PUB \n"
              << "\t WORLDMODEL_OTHER_VEHICLE_PUB \n"
              << "\t WORLDMODEL_OTHER_VEHICLE_CTRL \n"
              << "\t WORLDMODEL_SELF_VEHICLE_PUB \n"
              << std::endl;
}

}


}
