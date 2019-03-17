#ifndef _CVM_HMI_CONSOLEHMI_H_
#define _CVM_HMI_CONSOLEHMI_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/hmi/ProtocolMessageDebuger.h>
#include <cvm/hmi/ConsoleHMIConfig.h>

/**
 * @namespace cvm::hmi
 * @brief cvm::hmi
 */
namespace cvm
{
namespace hmi
{

class ConsoleHMI : public base::NonCopyable
{
public:
    ConsoleHMI(const ConsoleHMIConfig& config)
        : _config(config)
    {
        // lcm
        if (!_lcm.good()) {
            DIE("Lcm init error");
        }

        // Config
        if (_config.interestedChannel == "GPS_PUB") {
            _lcm.subscribe(CVM_CHANNEL_GPS_PUB,
                           &ProtocolMessageDebuger::debugGpsData, &_debuger);
        }
        if (_config.interestedChannel == "CAN_PUB") {
            _lcm.subscribe(CVM_CHANNEL_CAN_PUB,
                           &ProtocolMessageDebuger::debugCanData, &_debuger);
        }
        if (_config.interestedChannel == "CAN_CTRL") {
            _lcm.subscribe(CVM_CHANNEL_CAN_CTRL,
                           &ProtocolMessageDebuger::debugCanCtrlData, &_debuger);
        }
        if (_config.interestedChannel == "DSRC_BSM_PUB") {
            _lcm.subscribe(CVM_CHANNEL_DSRC_BSM_PUB,
                           &ProtocolMessageDebuger::debugBsmData, &_debuger);
        }
        if (_config.interestedChannel == "DSRC_BSM_CTRL") {
            _lcm.subscribe(CVM_CHANNEL_DSRC_BSM_CTRL,
                           &ProtocolMessageDebuger::debugBsmCtrlData, &_debuger);
        }
        if (_config.interestedChannel == "DSRC_MAP_PUB") {
            _lcm.subscribe(CVM_CHANNEL_DSRC_MAP_PUB,
                           &ProtocolMessageDebuger::debugMapData, &_debuger);
        }
        if (_config.interestedChannel == "DSRC_SPAT_PUB") {
            _lcm.subscribe(CVM_CHANNEL_DSRC_SPAT_PUB,
                           &ProtocolMessageDebuger::debugSpatData, &_debuger);
        }

        if (_config.interestedChannel == "WORLDMODEL_OTHER_VEHICLE_PUB") {
            _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_PUB,
                           &ProtocolMessageDebuger::debugOtherVehicleData, &_debuger);
        }
        if (_config.interestedChannel == "WORLDMODEL_OTHER_VEHICLE_CTRL") {
            _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_CTRL,
                           &ProtocolMessageDebuger::debugOtherVehicleCtrlData, &_debuger);
        }
        if (_config.interestedChannel == "WORLDMODEL_THIS_VEHICLE_PUB") {
            _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB,
                           &ProtocolMessageDebuger::debugSelfVehicleData, &_debuger);
        }

    }

    void loop()
    {
        while (_lcm.handle() == 0) {
            ;
        }
    }

private:
    lcm::LCM _lcm;
    ProtocolMessageDebuger _debuger;
    const ConsoleHMIConfig _config;
};

}

}

#endif // _CVM_HMI_CONSOLEHMI_H_
