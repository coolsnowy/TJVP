/**
  * @file CanConfig.h
  * @brief CAN的配置
  *
  */
#ifndef _CVM_SENSOR_CAN_CANCONFIG_H_
#define _CVM_SENSOR_CAN_CANCONFIG_H_

#include <string>

#define CVM_SENSOR_CAN_CONFIG_FILE "/etc/cvm/cvm-can.conf"

namespace cvm
{

namespace sensor
{

namespace can
{

/**
 * @class CanConfig
 * @brief 从配置文件解析Can的配置
 *
 */
struct CanConfig
{
    CanConfig(int argc, char** argv, const std::string& configFile);

    /**
     * @brief 输出配置的使用方法
     */
    static void printHelp();

    /**
     * @brief 输出当前的配置
     */
    void printConfig();

    // Data member
    std::string canInterfaceName;
    std::string logPath;
    int32_t canPublishIntervalMilisecond;
    int32_t canCtrlSendIntervalMilisecond;
    std::string carName;
    bool debug;
};

}

}

}

#endif // _CVM_SENSOR_CAN_CANCONFIG_H_
