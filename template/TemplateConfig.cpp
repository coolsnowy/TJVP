#include <iostream>

#include <cvm/base/Logging.h>
#include <template/TemplateConfig.h>

namespace cvm
{

namespace tpl
{

TemplateConfig::TemplateConfig(int argc, char** argv, const std::string& configFile)
{
    if (argc < 2) {
        DIE("HMI Config parse error");
    }

}

void TemplateConfig::printConfig()
{
}

void TemplateConfig::printHelp()
{
}

}


}
