#include <iostream>

#include <libconfig/libconfig.h++>

#include <cvm/base/Logging.h>
#include <cvm/sensor/gps/GpsConfig.h>

namespace cvm
{

namespace sensor
{

namespace gps {


GpsConfig::GpsConfig(int argc, char** argv, const std::string& configFile)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(configFile.data());
    }catch (const libconfig::FileIOException& e) {
        DIE("Can not open file %s \n", configFile.data());
    }catch (const libconfig::ParseException& e) {
        DIE("Can not parse file %s : %d %s \n",
            e.getFile(), e.getLine(), e.getError());
    }

    try {
        const libconfig::Setting& gps = cfg.lookup("gps");
        gps.lookupValue("debug", debug);
        gps.lookupValue("logPath", logPath);
        gps.lookupValue("serverIp", gpsdServerIp);
        gps.lookupValue("serverPort", gpsdServerPort);
    }catch (const libconfig::SettingNotFoundException& e) {
        DIE("Can not config value (%s) \n", e.what());
    }
}

void GpsConfig::printHelp()
{

}

void GpsConfig::printConfig()
{
    std::cout << "Gps start with \n"
              << "\t ServerIp="   << gpsdServerIp   << "\n"
              << "\t ServerPort=" << gpsdServerPort << "\n"
              << "\t Debug="   << (debug?"true":"false") << "\n"
              << "\t LogPath=" << logPath << "\n"
              << std::endl;

}


}

}

}
