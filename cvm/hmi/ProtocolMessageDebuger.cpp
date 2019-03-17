#include <assert.h>

#include <string>

#include <lcm/lcm-cpp.hpp>

#include <cvm/hmi/ProtocolMessageDebuger.h>

namespace cvm
{

namespace hmi
{

namespace internal
{

std::string turnLightToString(int8_t turnLight)
{
    if (turnLight == protocol::TurnLight::TurnNone) {
        return "TurnNone";
    }else if(turnLight == protocol::TurnLight::TurnRight) {
        return "TurnRight";
    }else if(turnLight == protocol::TurnLight::TurnLeft) {
        return "TurnLeft";
    }else {
        return "Unknown TurnLight";
    }
}

}

void ProtocolMessageDebuger::debugCanData(const lcm::ReceiveBuffer* rbuf,
                                          const std::string& channel,
                                          const protocol::CanData* msg)
{
    assert(channel == CVM_CHANNEL_CAN_PUB);
    std::cout << std::endl << "****************************************" << std::endl;
    std::cout << std::setprecision(10)
              << "Speed         = " << msg->speed              << std::endl
              << "Acceleration  = " << msg->acceleration       << std::endl
              << "SteeringWheelAngle = " << msg->steeringWheelAngle << std::endl
              << "TurnLight = " << internal::turnLightToString(msg->turnLight) << std::endl;
}

void ProtocolMessageDebuger::debugCanCtrlData(const lcm::ReceiveBuffer* rbuf,
                                              const std::string& channel,
                                              const protocol::CanCtrlData* msg)
{
    assert(channel == CVM_CHANNEL_CAN_CTRL);
    std::cout << std::endl << "****************************************" << std::endl;
    std::cout << std::setprecision(10)
              << "Id      = " << msg->id     << std::endl
              << "Length  = " << msg->length << std::endl
              << "Data    = ";

    for(int i=0; i<msg->length; i++) {
        std::cout << std::hex << (0xFF & msg->data[i]) << " ";
    }
    std::cout << std::endl;
}

void ProtocolMessageDebuger::debugGpsData(const lcm::ReceiveBuffer* rbuf,
                                          const std::string& channel,
                                          const protocol::GpsData* msg)
{
    assert(channel == CVM_CHANNEL_GPS_PUB);
    std::cout << std::endl << "****************************************" << std::endl;
    std::cout << std::setprecision(10)
              << "Latitude  = " << msg->location.latitude  << std::endl
              << "Longitude = " << msg->location.longitude << std::endl
              << "Altitude  = " << msg->location.altitude  << std::endl
              << "Speed     = " << msg->speed     << std::endl
              << "Quality   = " << msg->quality   << std::endl
              << "Azimuth   = " << msg->azimuth   << std::endl
              << "SatelliteNumber = " << msg->satelliteNumber << std::endl;
}

void ProtocolMessageDebuger::debugBsmData(const lcm::ReceiveBuffer* rbuf,
                                          const std::string& channel,
                                          const protocol::BsmData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_BSM_PUB);
    std::cout << std::endl << "****************************************" << std::endl;

    std::cout << std::setprecision(10)
              << "CarId = " << msg->carId << std::endl
              << "\t Longitude = " << msg->location.longitude << std::endl
              << "\t Latitude = "  << msg->location.latitude  << std::endl
              << "\t Azimuth = "   << msg->azimuth            << std::endl
              << "\t SteeringWheelAngle = " << msg->steeringWheelAngle << std::endl
              << "\t Speed = "        << msg->speed              << std::endl
              << "\t Acceleration = " << msg->acceleration       << std::endl;
}

void ProtocolMessageDebuger::debugBsmCtrlData(const lcm::ReceiveBuffer* rbuf,
                                              const std::string& channel,
                                              const protocol::BsmData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_BSM_CTRL);
    std::cout << std::endl << "****************************************" << std::endl;

    std::cout << std::setprecision(10)
              << "ThisVehicle" << std::endl
              << "\t Longitude = " << msg->location.longitude << std::endl
              << "\t Latitude = "  << msg->location.latitude  << std::endl
              << "\t Azimuth = "   << msg->azimuth            << std::endl
              << "\t SteeringWheelAngle = " << msg->steeringWheelAngle << std::endl
              << "\t Speed = "        << msg->speed              << std::endl
              << "\t Acceleration = " << msg->acceleration       << std::endl;
}

void ProtocolMessageDebuger::debugMapData(const lcm::ReceiveBuffer* rbuf,
                                          const std::string& channel,
                                          const protocol::MapData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_MAP_PUB);

    std::cout << std::endl << "****************************************" << std::endl;
    std::cout << "Intersection ID = " << std::setprecision(10) << msg->intersectionId << std::endl
              << "\t Approach Count = "  << msg->approachCount << std::endl
              << "\t RefPoint.Latitude = " << msg->refPoint.latitude << std::endl
              << "\t RefPoint.Longitude = " << msg->refPoint.longitude << std::endl
              << "\t RefPoint.Altitude = " << msg->refPoint.altitude << std::endl;

    for (int i=0; i<msg->approachCount; i++) {
        std::cout << "\t Approach ID = " << msg->approach[i].approachId << std::endl
                  << "\t\t Approach.RefPoint.Latitude = "
                  << msg->approach[i].refPoint.latitude << std::endl
                  << "\t\t Approach.RefPoint.Longitude = "
                  << msg->approach[i].refPoint.longitude << std::endl
                  << "\t\t Approach.RefPoint.Altitude = "
                  << msg->approach[i].refPoint.altitude << std::endl;
    }
}

void ProtocolMessageDebuger::debugSpatData(const lcm::ReceiveBuffer* rbuf,
                                           const std::string& channel,
                                           const protocol::SpatData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_SPAT_PUB);

    std::cout << std::endl << "****************************************" << std::endl;
    std::cout << "read spat data" << std::endl;
}

void ProtocolMessageDebuger::debugSelfVehicleData(const lcm::ReceiveBuffer* rbuf,
                                                  const std::string& channel,
                                                  const protocol::VehicleData* msg)
{
    std::cout << "********************" << std::endl;
    std::cout << std::setprecision(10)
              << "ThisVehicle" << std::endl
              << "\t Latitude  = " << msg->location.latitude  << std::endl
              << "\t Longitude = " << msg->location.longitude << std::endl
              << "\t Altitude  = " << msg->location.altitude  << std::endl
              << "\t SteeringWheelAngle = " << msg->steeringWheelAngle << std::endl
              << "\t Azimuth = "   << msg->azimuth << std::endl
              << "\t Speed     = " << msg->speed << std::endl
              << "\t TurnLight = " << internal::turnLightToString(msg->turnLight) << std::endl;
}

void ProtocolMessageDebuger::debugOtherVehicleData(const lcm::ReceiveBuffer* rbuf,
                                                   const std::string& channel,
                                                   const protocol::VehicleData* msg)
{
    std::cout << "********************" << std::endl;
    std::cout << std::setprecision(10)
              << "ThisVehicle" << std::endl
              << "\t Latitude  = " << msg->location.latitude  << std::endl
              << "\t Longitude = " << msg->location.longitude << std::endl
              << "\t Altitude  = " << msg->location.altitude  << std::endl
              << "\t SteeringWheelAngle = " << msg->steeringWheelAngle << std::endl
              << "\t Azimuth = "   << msg->azimuth << std::endl
              << "\t Speed     = " << msg->speed << std::endl
              << "\t TurnLight = " << internal::turnLightToString(msg->turnLight) << std::endl;
}

void ProtocolMessageDebuger::debugOtherVehicleCtrlData(const lcm::ReceiveBuffer* rbuf,
                                                       const std::string& channel,
                                                       const protocol::VehicleCtrlData* msg)
{
    std::cout << "********************" << std::endl;
    std::cout << "CarID = "        << msg->carId     << std::endl
              << "\t Operation = " << msg->operation << std::endl;
}


}

}
