/**
 * @file PushHMI.h
 * @brief PushHMI
 */
#ifndef _CVM_APPLICATION_PUSHHMI_PUSHHMI_H_
#define _CVM_APPLICATION_PUSHHMI_PUSHHMI_H_

#include <string>
#include <memory>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <map>

#include <cjson/cJSON.h>
#include <lcm/lcm-cpp.hpp>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/base/FileLogger.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/HmiWarnData.hpp>
#include <cvm/protocol/HmiVehicleData.hpp>
#include <cvm/protocol/HmiEventData.hpp>
#include <cvm/protocol/HmiRoadData.hpp>
#include <cvm/application/pushhmi/PushHMIConfig.h>


namespace cvm {

namespace application {

namespace pushhmi {

class PushHMI :public base::NonCopyable{

public:
    explicit PushHMI(const PushHMIConfig& config);
    ~PushHMI();

    void loop();

private:

    int hmi_sockfd_;
    std::string hmi_ip_;
    int hmi_port_;
    sockaddr_in hmi_sockaddr_;

    PushHMIConfig _config;
    base::EventLoop _loop;
    lcm::LCM _lcm;
    std::unique_ptr<base::Channel>  _lcmChannel;
    std::unique_ptr<base::FileLogger> _logger;

    std::shared_ptr<protocol::HmiWarnData> WarnData;
    std::map<int32_t, protocol::HmiEventData> EventData;
    std::shared_ptr<protocol::HmiRoadData> RoadData;
    std::shared_ptr<protocol::HmiVehicleData> VehicleData;

    void handleLcmHMIVehicleData(const lcm::ReceiveBuffer* rbuf,
                                 const std::string& channel,
                                 const protocol::HmiVehicleData* msg);
    void handleLcmHMIWarnData(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel,
                                  const protocol::HmiWarnData* msg);
    void handleLcmHMIRoadData(const lcm::ReceiveBuffer* rbuf,
                              const std::string& channel,
                              const protocol::HmiRoadData *msg);
    void handleLcmHMIEventData(const lcm::ReceiveBuffer* rbuf,
                               const std::string& channel,
                               const protocol::HmiEventData *msg);

    void sendUdpToHMI();

    /**
     * @brief 封装车辆数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateVehicle_Data();
    /**
     * @brief 封装路侧数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateRoad_Data();
    /**
     * @brief 封装事件数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateEvent_Data();
    /**
     * @brief 封装预警数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateWarning_Data();

};

}

}

}

#endif
