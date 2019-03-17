#ifndef _CVM_HMI_CONSOLEHMICONFIG_H_
#define _CVM_HMI_CONSOLEHMICONFIG_H_

#include <string>

namespace cvm
{

namespace hmi
{

struct ConsoleHMIConfig
{
    // Parser
    ConsoleHMIConfig(int argc, char** argv, const std::string& configFile);

    void printConfig();
    static void printHelp();

    // Data
    std::string interestedChannel;
};

}

}

#endif // _CVM_HMI_CONSOLEHMICONFIG_H_
