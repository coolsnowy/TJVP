/**
  * @file WorldModelConfig.h
  * @brief WorldModel的配置
  */
#ifndef _CVM_WORLDMODEL_WORLDMODELCONFIG_H_
#define _CVM_WORLDMODEL_WORLDMODELCONFIG_H_

#include <string>

#define CVM_WORLDMODEL_CONFIG_FILE "/etc/cvm/cvm-worldmodel.conf"

namespace cvm
{

namespace worldmodel
{

/**
 * @class WorldModelConfig
 * @brief 从配置文件解析WorldModel的配置
 *
 */
struct WorldModelConfig
{
    WorldModelConfig(int argc, char** argv, const std::string& configFile);

    /**
     * @brief 输出配置的使用方法
     */
    static void printHelp();

    /**
     * @brief 输出当前的配置
     */
    void printConfig();

    // Data members
    bool debug;
    std::string logPath;
};

}

}

#endif // _CVM_WORLDMODEL_WORLDMODELCONFIG_H_
