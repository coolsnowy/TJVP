#include <cvm/application/eventdetect/EventDetectConfig.h>

namespace cvm {

namespace application {

namespace eventdetect {

EventDetectConfig::EventDetectConfig(int argc, char **argv, const std::string &configFile){
    libconfig::Config cfg;

    try {
        cfg.readFile(CVM_APPLICATION_EVENTDETECT_CONFIG_FILE);
    }catch (const libconfig::FileIOException& e) {
        DIE("Can not open file %s \n", CVM_APPLICATION_EVENTDETECT_CONFIG_FILE);
    }catch (const libconfig::ParseException& e) {
        DIE("Can not parse file %s : %d %s \n",
            e.getFile(), e.getLine(), e.getError());
    }

    try {
        const libconfig::Setting& can = cfg.lookup("EventGPS");
        can.lookupValue("debug", debug);
        can.lookupValue("logPath", logPath);
        can.lookupValue("latitude", latitude);
        can.lookupValue("longitude", longitude);
    }catch (const libconfig::SettingNotFoundException& e) {
        DIE("Can not config value (%s) \n", e.what());
    }
}


void EventDetectConfig::printHelp(){

}

void EventDetectConfig::printConfig(){
    std::cout << "EventGPS Config : \n"
              << "\t Debug = "   << (debug?"true":"false") << "\n"
              << "\t LogPath = " << logPath << "\n"
              << "\t latitude = " << latitude << "\n"
              << "\t longitude = " << longitude << "\n"
              << std::endl;
}




}

}

}
