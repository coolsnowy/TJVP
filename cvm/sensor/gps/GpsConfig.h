/**
  * @file GpsConfig.h
  * @brief Gps的配置
  */
#ifndef _CVM_SENSOR_GPS_GPSCONFIG_H_
#define _CVM_SENSOR_GPS_GPSCONFIG_H_

#include <string>

#define CVM_SENSOR_GPS_CONFIG_FILE "/etc/cvm/cvm-gps.conf"

namespace cvm
{

namespace sensor
{

namespace gps
{

/**
 * @class GpsConfig
 * @brief 从配置文件解析Gps的配置
 *
 */
struct GpsConfig
{
    GpsConfig(int argc, char** argv, const std::string& configFile);

    /**
     * @brief 输出配置的使用方法
     */
    static void printHelp();

    /**
     * @brief 输出当前的配置
     */
    void printConfig();

    // Data member
    std::string gpsdServerIp;
    std::string gpsdServerPort;
    std::string logPath;
    bool debug;
};

}

}

}

#endif // _CVM_SENSOR_GPS_GPSCONFIG_H_
