#include <fstream>
#include <string>
#include <cmath>
#include <iostream>

#include <sys/socket.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/timerfd.h>
#include <sys/select.h>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>

#include <cvm/sensor/dsrc/J2735.h>
#include <cvm/sensor/dsrc/Dsrc.h>
#include <cvm/protocol/Approach.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>
#include <cvm/protocol/ProtocolChannel.h>

namespace cvm
{

namespace sensor
{

namespace dsrc
{

Dsrc::Dsrc(const DsrcConfig& config)
    : _loop("dsrcd"),
      _config(config)
{
    // Logger
    if (!_config.debug) {
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Info,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush, &*_logger, std::placeholders::_1));
    }else {
        base::Logging::setLogLevel(base::Logging::Debug);
    }

    LINFO << "Loop start";

    // Lcm
    if (!_lcm.good()) {
        LDIE << "lcm init error";
    }

    _lcm.subscribe(CVM_CHANNEL_DSRC_BSM_CTRL, &Dsrc::handleLcmReadBsmCtrl, this);
    _lcmChannel.reset(new base::Channel(&_loop, _lcm.getFileno(), "lcm"));
    _lcmChannel->setReadCallback(std::bind(&lcm::LCM::handle, &_lcm));
    _lcmChannel->enableReading();

    // Dsrc
    _dsrcFd = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (_dsrcFd < 0) {
        LDIE << "dsrc open error";
    }
    struct sockaddr_in address;
    ::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(_config.localPort.data()));
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (::bind(_dsrcFd, reinterpret_cast<struct sockaddr*>(&address),
               sizeof(address)) < 0) {
        LDIE << "dsrc fd(" << _dsrcFd << ") bind " << _config.localPort << " error";
    }
    LINFO << "dsrc bind " << _config.localPort;
    _dsrcChannel.reset(new base::Channel(&_loop, _dsrcFd));
    _dsrcChannel->setReadCallback(std::bind(&Dsrc::handleDsrcRead, this));
    _dsrcChannel->enableReading();

}

Dsrc::~Dsrc()
{
    _lcmChannel->remove();
    _dsrcChannel->remove();
    ::close(_dsrcFd);

    LINFO << "Loop end";
}

void Dsrc::loop()
{
    _loop.loop();
}

void Dsrc::handleDsrcRead()
{
//    std::cout<<"receive message from dsrc!"<<std::endl;
    ssize_t n = ::recvfrom(_dsrcFd, _dsrcData, sizeof(_dsrcData), 0, nullptr, nullptr);
//    for(int iii = 0;iii<n;iii++) {
//        printf("%02X\t",_dsrcData[iii]);
//    }printf("\n");
    if (n <= 0) {
        LWARN << "dsrcfd recvfrom error";
        return ;
    }

    LDEBUG << "recv " << n << " bytes";
    /* use protocol j2735 */
    if(_config.protocol == "J2735"){
        int lengthBytes = 1;
        ///
        /// DER Encoding/Decoding details are in luca.ntop.org/Teaching/Appunti/asn1.html
        ///     especially in secion 3 and section 4
        /// That bit-8 euqals 1 means long form length(ge than 128),
        ///     otherwise short form length(0 ~ 127)
        ///
        if (_dsrcData[1] & 0x80) {
            lengthBytes = _dsrcData[1] & 0x7F;
            lengthBytes += 1;
        }

        // tag + length + subtag + length
        int msgType = _dsrcData[1 + lengthBytes + 1 + 1];
        //LDEBUG << "Message Type" << msgType;
        switch (msgType) {
        // Bsm
        case 2:
//            std::cout<<"###receive bsm message"<<std::endl;
            _bsmData = bsmDataDecode(_dsrcData, n);
            if (_bsmData.carId == -1) {
                LWARN << "recv bsm with wrong binary format";
            }else {
                _lcm.publish(CVM_CHANNEL_DSRC_BSM_PUB, &_bsmData);
                LINFO << "send bsm on channel " << CVM_CHANNEL_DSRC_BSM_PUB;
            }
            break;
            // Map
        case 7:
//            std::cout<<"###receive map message"<<std::endl;
            _mapData = mapDataDecode(_dsrcData, n);
            std::cout<<_mapData.intersectionId<<std::endl;
            if (_mapData.intersectionId == -1) {
                LWARN << "recv map with wrong binary format";
            }else {
                _lcm.publish(CVM_CHANNEL_DSRC_MAP_PUB, &_mapData);
                LINFO << "send map on channel " << CVM_CHANNEL_DSRC_MAP_PUB;
            }
            break;
            // Spat
        case 13:
//            std::cout<<"###receive spat message"<<std::endl;
            _spatData = spatDataDecode(_dsrcData, n);
            if (_spatData.intersectionId == -1) {
                std::cout<<"spat wrrong"<<std::endl;
                LWARN << "recv spat with wrong binary format";
            }else {
                std::cout<<"spat published"<<std::endl;
                _lcm.publish(CVM_CHANNEL_DSRC_SPAT_PUB, &_spatData);
                LINFO << "send spat on channel " << CVM_CHANNEL_DSRC_SPAT_PUB;
            }
            break;
            default:
            LWARN << "unknown j2735 msg type(message type = " << msgType << ")";
            break;
        }
    }
    else if(_config.protocol == "C-ITS"){/* use protocol C-ITS */

    }
    else if(_config.protocol == "J2735&C-ITS"){/* use protocol J2735 & C-ITS,use different decode method according to the data*/

    }
}

void Dsrc::handleLcmReadBsmCtrl(const lcm::ReceiveBuffer* rbuf,
                                const std::string& channel,
                                const protocol::BsmData* msg)
{
    assert(channel == CVM_CHANNEL_DSRC_BSM_CTRL);

    auto data = bsmDataEncode(*msg);
    if (data.empty()) {
        LWARN << "bsm encode error";
        return ;
    }
    int n = ::sendto(_dsrcFd, data.data(), data.size(), 0,
                     reinterpret_cast<sockaddr*>(&_config.remoteAddress),
                     sizeof(_config.remoteAddress));
    LINFO << "send encoded bsm(" << n << "bytes) to "
          << _config.remoteIp << ":" << _config.remotePort;
}

}

}

}
