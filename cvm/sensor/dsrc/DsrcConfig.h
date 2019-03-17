/**
  * @file DsrcConfig.h
  * @brief DSRC的配置
  */
#ifndef _CVM_SENSOR_DSRC_DSRCCONFIG_H_
#define _CVM_SENSOR_DSRC_DSRCCONFIG_H_

#include <string>

#include <netinet/in.h>

#define CVM_SENSOR_DSRC_CONFIG_FILE "/etc/cvm/cvm-dsrc.conf"

namespace cvm
{

namespace sensor
{

namespace dsrc
{

/**
 * @class DsrcConfig
 * @brief 从配置文件解析Dsrc的配置
 *
 */
struct DsrcConfig
{
    DsrcConfig(int argc, char** argv, const std::string& configFile);

     /**
     * @brief 输出配置的使用方法
     */
    static void printHelp();

     /**
     * @brief 输出当前的配置
     */
    void printConfig();

    // Data members
    std::string remoteIp;
    std::string remotePort;
    std::string localPort;
    std::string protocol;
    bool        debug;
    std::string logPath;
    struct sockaddr_in remoteAddress;

};


}

}

}

#endif // _CVM_SENSOR_DSRC_DSRCCONFIG_H_
