#ifndef _TEMPLATECONFIG_H_
#define _TEMPLATECONFIG_H_

#include <string>

namespace cvm
{

namespace tpl
{

struct TemplateConfig
{
    // Parse in constructor
    TemplateConfig(int argc, char** argv, const std::string& configFile);

    void printConfig();
    void printHelp();

    // Config Data member
};

}

}

#endif // _TEMPLATECONFIG_H_
