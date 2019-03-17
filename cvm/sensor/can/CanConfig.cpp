#include <iostream>

#include <libconfig/libconfig.h++>

#include <cvm/base/Logging.h>
#include <cvm/sensor/can/CanConfig.h>

namespace cvm
{

namespace sensor
{

namespace can
{

CanConfig::CanConfig(int argc, char **argv, const std::string &configFile)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(CVM_SENSOR_CAN_CONFIG_FILE);
    }catch (const libconfig::FileIOException& e) {
        DIE("Can not open file %s \n", CVM_SENSOR_CAN_CONFIG_FILE);
    }catch (const libconfig::ParseException& e) {
        DIE("Can not parse file %s : %d %s \n",
            e.getFile(), e.getLine(), e.getError());
    }

    try {
        const libconfig::Setting& can = cfg.lookup("can");
        can.lookupValue("debug", debug);
        can.lookupValue("logPath", logPath);
        can.lookupValue("carName", carName);
        can.lookupValue("canPublishIntervalMilisecond", canPublishIntervalMilisecond);
        can.lookupValue("canCtrlSendIntervalMilisecond", canCtrlSendIntervalMilisecond);
        can.lookupValue("canInterfaceName", canInterfaceName);
    }catch (const libconfig::SettingNotFoundException& e) {
        DIE("Can not config value (%s) \n", e.what());
    }
}

void CanConfig::printHelp()
{

}

void CanConfig::printConfig()
{
    std::cout << "Can Config : \n"
              << "\t Debug = "   << (debug?"true":"false") << "\n"
              << "\t LogPath = " << logPath << "\n"
              << "\t CanInterfaceName = " << canInterfaceName << "\n"
              << "\t CarName = " << carName << "\n"
              << "\t canPublishIntervalMilisecond = "  << canPublishIntervalMilisecond  << "\n"
              << "\t canCtrlSendIntervalMilisecond = " << canCtrlSendIntervalMilisecond << "\n"
              << std::endl;
}

}

}

}




