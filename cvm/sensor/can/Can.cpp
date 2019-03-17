#include <assert.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <math.h>

#include <map>
#include <functional>
#include <queue>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/Channel.h>
#include <cvm/base/Logging.h>
#include <cvm/sensor/can/Can.h>
#include <cvm/sensor/can/CanConfig.h>
#include <cvm/sensor/can/CanDecoder.h>
#include <cvm/sensor/can/CanTransmitterFactory.h>
#include <cvm/sensor/can/CanDecoderFactory.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/CanCtrlData.hpp>
#include <cvm/protocol/TurnLight.hpp>

namespace cvm
{

namespace sensor
{

namespace can
{

Can::Can(const CanConfig& config)
{
    // Decoder
    CanDecoderFactory& canDecoderFactory = CanDecoderFactory::instance();
    CanDecoderIdentifier canDecoderIdentifier;
    if (config.carName == "PanAsia") {
        canDecoderIdentifier = PanAsia;
    }else if (config.carName == "RoeweE50") {
        canDecoderIdentifier = RoeweE50;
    }else if (config.carName == "Baic") {
        canDecoderIdentifier = Baic;
    }

    _decoder = canDecoderFactory.createObject(canDecoderIdentifier);

    // Transmitter
    CanTransmitterFactory& canTransmitterFactory = CanTransmitterFactory::instance();
    CanTransmitterIdentifier canTransmitterIdentifier = SocketCan;
    if (1) {
        _transmitter = canTransmitterFactory.createObject(canTransmitterIdentifier, config, _decoder.get());
    }
}

Can::~Can()
{
}

void Can::loop()
{
    _transmitter->loop();
}

}

}

}
