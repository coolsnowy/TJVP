#include <iostream>

#include <libconfig/libconfig.h++>

#include <cvm/base/Logging.h>
#include <cvm/worldmodel/WorldModelConfig.h>

namespace cvm
{

namespace worldmodel
{

WorldModelConfig::WorldModelConfig(int argc, char** argv, const std::string& configFile)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(CVM_WORLDMODEL_CONFIG_FILE);
    }catch (const libconfig::FileIOException& e) {
        DIE("Can not open file %s \n", CVM_WORLDMODEL_CONFIG_FILE);
    }catch (const libconfig::ParseException& e) {
        DIE("Can not parse file %s : %d %s \n",
            e.getFile(), e.getLine(), e.getError());
    }

    try {
        const libconfig::Setting& world = cfg.lookup("worldmodel");
        world.lookupValue("debug", debug);
        world.lookupValue("logPath", logPath);
    }catch (const libconfig::SettingNotFoundException& e) {
        DIE("Can not config value (%s) \n", e.what());
    }
}

void WorldModelConfig::printHelp()
{
}

void WorldModelConfig::printConfig()
{
    std::cout << "WorldModel start with \n"
              << "\t Debug="   << (debug?"true":"false") << "\n"
              << "\t LogPath=" << logPath << "\n"
              << std::endl;

}

}
}
