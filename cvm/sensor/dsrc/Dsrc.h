/**
  * @file Dsrc.h
  * @brief Dsrc类的定义
  */
#ifndef _CVM_SENSOR_DSRC_DSRC_H_
#define _CVM_SENSOR_DSRC_DSRC_H_

#include <fstream>
#include <string>
#include <cmath>
#include <iostream>


#include <lcm/lcm-cpp.hpp>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>

#include <cvm/sensor/dsrc/DsrcConfig.h>
#include <cvm/protocol/Approach.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>
#include <cvm/protocol/BsmData.hpp>
#include <cvm/protocol/ProtocolChannel.h>

/**
 * @namespace cvm::sensor::dsrc
 * @brief cvm::sensor::dsrc
 */
namespace cvm
{

namespace sensor
{

namespace dsrc
{
/**
 * @class Dsrc
 * @brief 和Dsrc设备收发数据，同时提供J2735的编解码功能
 *
 * 通过UDP和DSRC设备交互：接收其他DSRC设备的BSM数据并解析，在CVM_CHANNEL_DSRC_BSM_PUB中广播；在CVM_CHANNEL_DSRC_BSM_CTRL接受世界模型层发出的BSM数据，编码后发给DSRC设备
 *
 */
class Dsrc : public base::NonCopyable
{
public:

    Dsrc(const DsrcConfig& config);
    ~Dsrc();
    void loop();

private:

    void handleDsrcRead();

    void handleLcmReadBsmCtrl(const lcm::ReceiveBuffer* rbuf,
                              const std::string& channel,
                              const protocol::BsmData* msg);

    DsrcConfig _config;

    base::EventLoop _loop;

    lcm::LCM _lcm;
    int _dsrcFd;

    std::unique_ptr<base::Channel> _lcmChannel;//从平台往v2xd进程发送bsm数据的信道
    std::unique_ptr<base::Channel> _dsrcChannel;//从v2xd进程往平台读取数据的信道

    char _dsrcData[2048]; // J2735 data length should not be longer than 2048
    protocol::MapData _mapData;
    protocol::BsmData _bsmData;
    protocol::SpatData _spatData;

    std::unique_ptr<base::FileLogger> _logger;
};


}


}


}

#endif // _CVM_SENSOR_DSRC_DSRCD_H_
