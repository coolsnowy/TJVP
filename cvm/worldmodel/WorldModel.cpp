#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/GpsData.hpp>
#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/VehicleCtrlData.hpp>
#include <cvm/protocol/IntersectionData.hpp>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/BlockingQueue.h>
#include <cvm/worldmodel/WorldModelConfig.h>
#include <cvm/worldmodel/WorldModel.h>
#include <cvm/worldmodel/Intersection.h>
#include <iostream>
namespace cvm
{

namespace worldmodel
{


WorldModel::WorldModel(const WorldModelConfig& config)
    : _loop("worldmodel"),
      _config(config)
{
    // Logger
    if (_config.debug) {
        base::Logging::setLogLevel(base::Logging::Debug);
    }else {
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Debug,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush, &*_logger, std::placeholders::_1));

    }

    // Lcm
    if (!_lcm.good()) {
        LDIE << "lcm init error";
    }
    _lcm.subscribe(CVM_CHANNEL_GPS_PUB, &WorldModel::handleLcmReadGps, this);
    _lcm.subscribe(CVM_CHANNEL_CAN_PUB, &WorldModel::handleLcmReadCan, this);
    _lcm.subscribe(CVM_CHANNEL_DSRC_BSM_PUB, &WorldModel::handleLcmReadBsm, this);
    _lcm.subscribe(CVM_CHANNEL_DSRC_MAP_PUB, &WorldModel::handleLcmReadMap, this);
    _lcm.subscribe(CVM_CHANNEL_DSRC_SPAT_PUB, &WorldModel::handleLcmReadSpat, this);

    _lcmChannel.reset(new cvm::base::Channel(&_loop, _lcm.getFileno(), "lcm"));
    _lcmChannel->setReadCallback(std::bind(&lcm::LCM::handle, &_lcm));
    _lcmChannel->enableReading();

    _loop.runEvery(100, std::bind(&WorldModel::sendBsm, this));
    _loop.runEvery(2 * 1000, std::bind(&WorldModel::clearExpiredItems, this));
}

WorldModel::~WorldModel()
{
    LINFO << "loop end";
}


void WorldModel::handleLcmReadGps(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel, const protocol::GpsData* msg)
{
    assert(channel == CVM_CHANNEL_GPS_PUB);
    _vehicles.updateFromGps(msg);
    _lcm.publish(CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB,
                 _vehicles.getThisVehicleData());
}

void WorldModel::handleLcmReadCan(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel, const protocol::CanData* msg)
{
    assert(channel == CVM_CHANNEL_CAN_PUB);
    _vehicles.updateFromCan(msg);
    _lcm.publish(CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB,
                 _vehicles.getThisVehicleData());
}

void WorldModel::handleLcmReadBsm(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel, const protocol::BsmData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_BSM_PUB);
    int32_t carId = _vehicles.updateFromBsm(msg);
    _lcm.publish(CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_PUB,
                 _vehicles.getOtherVehicleData(carId));
}

void WorldModel::handleLcmReadMap(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel, const protocol::MapData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_MAP_PUB);
    _intersections.updateFromMap(msg);
}

void WorldModel::handleLcmReadSpat(const lcm::ReceiveBuffer* rbuf,
                                   const std::string& channel, const protocol::SpatData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_SPAT_PUB);
    _intersections.updateFromSpat(msg);
    _lcm.publish(CVM_CHANNEL_WORLDMODEL_INTERSECTION_PUB, _intersections.getAnIntersection(msg->intersectionId));
    //_intersections.chooseLight(_vehicles.getThisVehicleData());

}

void WorldModel::loop()
{
    LINFO << "Loop start";

    _loop.loop();

    LINFO << "loop end";
}

void WorldModel::clearExpiredItems()
{
    std::vector<int32_t> carIds = _vehicles.clearTimeoutVehicles();
    LDEBUG << carIds.size();
    cvm::protocol::VehicleCtrlData vehicleCtrlData;
    vehicleCtrlData.operation = 1; // ?
    for (auto carId : carIds) {
        vehicleCtrlData.carId = carId;
        _lcm.publish(CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_CTRL,
                     &vehicleCtrlData);
    }
}

void WorldModel::sendBsm()
{
    protocol::BsmData bsmData;
    const protocol::VehicleData* thisVehicle = _vehicles.getThisVehicleData();
    bsmData.carId = thisVehicle->carId;
    bsmData.acceleration = thisVehicle->acceleration;
    bsmData.azimuth = thisVehicle->azimuth;
    bsmData.location = thisVehicle->location;
    bsmData.speed = thisVehicle->speed;
    bsmData.steeringWheelAngle = thisVehicle->steeringWheelAngle;
    _lcm.publish(CVM_CHANNEL_DSRC_BSM_CTRL, &bsmData);
}

}

}
