#ifndef _CVM_HMI_PROTOCOLMESSAGEDEBUGER_H_
#define _CVM_HMI_PROTOCOLMESSAGEDEBUGER_H_

#include <iostream>
#include <iomanip>

#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/CanCtrlData.hpp>
#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/TurnLight.hpp>
#include <cvm/protocol/GpsData.hpp>
#include <cvm/protocol/BsmData.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/VehicleCtrlData.hpp>

namespace cvm
{

namespace hmi
{

struct ProtocolMessageDebuger
{
    void debugCanData(const lcm::ReceiveBuffer* rbuf,
                      const std::string& channel,
                      const protocol::CanData* msg);

    void debugCanCtrlData(const lcm::ReceiveBuffer* rbuf,
                          const std::string& channel,
                          const protocol::CanCtrlData* msg);

    void debugGpsData(const lcm::ReceiveBuffer* rbuf,
                      const std::string& channel,
                      const protocol::GpsData* msg);

    void debugBsmData(const lcm::ReceiveBuffer* rbuf,
                      const std::string& channel,
                      const protocol::BsmData* msg);

    void debugBsmCtrlData(const lcm::ReceiveBuffer* rbuf,
                          const std::string& channel,
                          const protocol::BsmData* msg);

    void debugMapData(const lcm::ReceiveBuffer* rbuf,
                      const std::string& channel,
                      const protocol::MapData* msg);

    void debugSpatData(const lcm::ReceiveBuffer* rbuf,
                       const std::string& channel,
                       const protocol::SpatData* msg);

    void debugSelfVehicleData(const lcm::ReceiveBuffer* rbuf,
                              const std::string& channel,
                              const protocol::VehicleData* msg);

    void debugOtherVehicleData(const lcm::ReceiveBuffer* rbuf,
                               const std::string& channel,
                               const protocol::VehicleData* msg);

    void debugOtherVehicleCtrlData(const lcm::ReceiveBuffer* rbuf,
                                   const std::string& channel,
                                   const protocol::VehicleCtrlData* msg);
};

}

}

#endif // _CVM_HMI_PROTOCOLMESSAGEDEBUGER_H_
