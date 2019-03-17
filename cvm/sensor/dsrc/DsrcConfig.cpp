#include <iostream>

#include <sys/socket.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <libconfig/libconfig.h++>

#include <cvm/base/Logging.h>
#include <cvm/sensor/dsrc/DsrcConfig.h>

namespace cvm
{

namespace sensor
{

namespace dsrc
{


DsrcConfig::DsrcConfig(int argc, char** argv, const std::string& configFile)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(CVM_SENSOR_DSRC_CONFIG_FILE);
    }catch (const libconfig::FileIOException& e) {
        DIE("Can not open file %s \n", CVM_SENSOR_DSRC_CONFIG_FILE);
    }catch (const libconfig::ParseException& e) {
        DIE("Can not parse file %s : %d %s \n",
            e.getFile(), e.getLine(), e.getError());
    }

    try {
        const libconfig::Setting& dsrc = cfg.lookup("dsrc");
        dsrc.lookupValue("remoteIp", remoteIp);
        dsrc.lookupValue("remotePort", remotePort);
        dsrc.lookupValue("localPort", localPort);
        dsrc.lookupValue("protocol", protocol);
        dsrc.lookupValue("debug", debug);
        dsrc.lookupValue("logPath", logPath);
    }catch (const libconfig::SettingNotFoundException& e) {
        DIE("Can not config value (%s) \n", e.what());
    }

    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_port = htons(atoi(remotePort.data()));
    remoteAddress.sin_addr.s_addr = inet_addr(remoteIp.data());
}

void DsrcConfig::printHelp()
{

}

void DsrcConfig::printConfig()
{
    std::cout << "Dsrc start with \n"
              << "\t RemoteIp = "   << remoteIp   << "\n"
              << "\t RemotePort = " << remotePort << "\n"
              << "\t LocalPort = "  << localPort  << "\n"
              << "\t Protocol = "   << protocol   << "\n"
              << "\t Debug = "      << (debug?"true":"false") << "\n"
              << "\t LogPath = "    << logPath
              << std::endl;

}

}

}

}
