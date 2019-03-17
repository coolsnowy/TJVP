#include <paho-mqtt/Clients.h>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Channel.h>
#include <cvm/base/EventLoop.h>

#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/VehicleCtrlData.hpp>

#define CVM_APPLICATION_UPLOAD_VERSION 0.1

namespace cvm
{

namespace application
{

namespace upload
{

class Uploadd : public base::NonCopyable
{
public:
    Uploadd(const std::string& clientID,
            const std::string& serverAddress,
            const std::string& serverPort,
            const std::string& username = "",
            const std::string& password = "",
            const std::string& topic = "DSRC",
            bool debug = true,
            const std::string& logPath = "")
        : _clientID(clientID),
          _serverAddress(serverAddress),
          _serverPort(serverPort),
          _username(username),
          _password(password),
          _topic(topic),
          _debug(debug),
          _logPath(logPath),
          _connectOptions(MQTTClient_connectOptions_initializer)
    {
        // Logger
        if (_debug) {
            base::Logging::setLogLevel(base::Logging::Debug);
        }else {
            _logger.reset(new base::FileLogger(2, false, _logPath));
            base::Logging::initLogging(base::Logging::Debug,
                       std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                       std::bind(&base::FileLogger::flush, &*_logger, std::placeholders::_1));

        }

        LINFO << "Upload version = " << CVM_APPLICATION_UPLOAD_VERSION;
        LINFO << "Upload start with \n"
              << "\t Debug = "   << (_debug?"true":"false") << "\n"
              << "\t LogPath = " << _logPath;

        // Lcm
        if (!_lcm.good()) {
            LDIE << "lcm init error";
        }

        _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB,
                       &Uploadd::handleLcmReadThisVehicleData, this);

        // mqtt
        const std::string serverURI = "tcp://" + _serverAddress + ":" + _serverPort;
        int rc = MQTTClient_create(&_client, serverURI.data(), _clientID.data(),
                                   MQTTCLIENT_PERSISTENCE_DEFAULT, NULL);
        if (rc != MQTTCLIENT_SUCCESS) {
            MQTTClient_destroy(&_client);
            LDIE << "mqtt init error";
        }

        _connectOptions.keepAliveInterval = 20;
        _connectOptions.cleansession = 1;
        _connectOptions.username = _username.data();
        _connectOptions.password = _password.data();
        _connectOptions.connectTimeout = 5;
        _connectOptions.retryInterval = 3;
        _connectOptions.MQTTVersion = MQTTVERSION_DEFAULT;

        if (MQTTClient_connect(_client, &_connectOptions) != MQTTCLIENT_SUCCESS) {
            MQTTClient_destroy(&_client);
            LDIE << "mqtt connect error";
        }
    }

    ~Uploadd()
    {
        MQTTClient_disconnect(_client, 0);
        MQTTClient_destroy(&_client);
    }

    void loop()
    {
        LINFO << "Loop start";
//        while (_lcm.handle() == 0) {
//            ;
//        }
        protocol::VehicleData msg;
        msg.carId = 666;
        msg.acceleration = 0;
        msg.azimuth = 0;
        msg.speed = 10;
        msg.steeringWheelAngle = 30;
        msg.location.latitude = 50;
        msg.location.longitude = 100;
        while (1) {
            sleep(1);
            handleLcmReadThisVehicleData(nullptr, "", &msg);
        }
        LINFO << "Loop end";
    }

private:

    void handleLcmReadThisVehicleData(const lcm::ReceiveBuffer* rbuf, const std::string& channel,
                       const protocol::VehicleData* msg)
    {
        MQTTClient_message mqtt = MQTTClient_message_initializer;

        char buffer[2048] = "\0";
        int length = snprintf(buffer, sizeof(buffer), s_jsonTemplate, msg->carId, msg->speed,
                 msg->azimuth, msg->location.latitude, msg->location.longitude);
        mqtt.payload    = buffer;
        mqtt.payloadlen = length;
        mqtt.qos      = 0;
        mqtt.retained = 0;

        int ret = MQTTClient_publishMessage(_client, _topic.data(), &mqtt, nullptr);
        LDEBUG << "Content = "     << buffer;
    }


    lcm::LCM _lcm;
    std::unique_ptr<base::FileLogger> _logger;

    MQTTClient _client;
    MQTTClient_connectOptions _connectOptions;

    const std::string _clientID;
    const std::string _serverAddress;
    const std::string _serverPort;
    const std::string _username;
    const std::string _password;
    const std::string _topic;
    const bool _debug;
    const std::string _logPath;

    static const char* s_jsonTemplate;
};

const char* Uploadd::s_jsonTemplate = "{"
                                        "\"CarID\" : %d, "
                                        "\"Speed\" : %f, "
                                        "\"Azimuth\"   : %f, "
                                        "\"Latitude\"  : %f, "
                                        "\"Longitude\" : %f  "
                                      "}";

}

}

}

int main()
{
    cvm::application::upload::Uploadd uploadd("Client1", "123.56.216.160", "1883");
    uploadd.loop();
    return 0;
}
