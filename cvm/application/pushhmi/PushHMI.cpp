#include <cvm/application/pushhmi/PushHMI.h>

namespace cvm {

namespace application {

namespace pushhmi {

PushHMI::PushHMI(const PushHMIConfig& config)
    :_loop("pushhmi"),
     _config(config),
     hmi_ip_("192.168.1.101"),
     hmi_port_(4040)
{
    if(!_config.debug){
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Info,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush,&*_logger,std::placeholders::_1));
    }else{
        base::Logging::setLogLevel(base::Logging::Debug);
    }

    hmi_sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if(hmi_sockfd_ == -1){
        LDIE<<"pushhmi socket init error! ";
    }
    memset(&hmi_sockaddr_, 0, sizeof(sockaddr_in));
    hmi_sockaddr_.sin_family = AF_INET;
    hmi_sockaddr_.sin_port = htons(hmi_port_);
    hmi_sockaddr_.sin_addr.s_addr = inet_addr(hmi_ip_.c_str());

    if(!_lcm.good()){
        LDIE<<"lcm init error";
    }

    WarnData.reset(new protocol::HmiWarnData);
    EventData.clear();
//    EventData.reset(new protocol::HmiEventData);
    RoadData.reset(new protocol::HmiRoadData);
    VehicleData.reset(new protocol::HmiVehicleData);

    _lcm.subscribe(CVM_CHANNEL_HMI_VEHICLE_PUB,
                   &PushHMI::handleLcmHMIVehicleData,this);
    _lcm.subscribe(CVM_CHANNEL_HMI_WARN_PUB,
                   &PushHMI::handleLcmHMIWarnData,this);
    _lcm.subscribe(CVM_CHANNEL_HMI_ROAD_PUB,
                   &PushHMI::handleLcmHMIRoadData,this);
    _lcm.subscribe(CVM_CHANNEL_HMI_EVENT_PUB,
                   &PushHMI::handleLcmHMIEventData,this);

    _lcmChannel.reset(new base::Channel(&_loop, _lcm.getFileno(), "lcm"));
    _lcmChannel->setReadCallback(std::bind(&lcm::LCM::handle, &_lcm));
    _lcmChannel->enableReading();

    _loop.runEvery(100,std::bind(&PushHMI::sendUdpToHMI, this));


}

PushHMI::~PushHMI(){

    close(hmi_sockfd_);
    _lcmChannel->remove();
    LINFO<<"Loop end";

}

void PushHMI::loop(){

    LINFO<<" Loop start";

    _loop.loop();
    LINFO<<" Loop end";
}

/**
 * @brief PushHMI::handleLcmHMIVehicleData
 * @param rbuf
 * @param channel
 * @param msg
 */
void PushHMI::handleLcmHMIVehicleData(const lcm::ReceiveBuffer *rbuf,

                                      const std::string &channel, const protocol::HmiVehicleData *msg){
    assert(channel == CVM_CHANNEL_HMI_VEHICLE_PUB);
    std::shared_ptr<protocol::HmiVehicleData> temp_Vehicle = std::make_shared<protocol::HmiVehicleData>(*msg);
    VehicleData.swap(temp_Vehicle);
}
/**
 * @brief PushHMI::handleLcmHMIRoadData
 * @param rbuf
 * @param channel
 * @param msg
 */
void PushHMI::handleLcmHMIRoadData(const lcm::ReceiveBuffer *rbuf,
                                   const std::string &channel, const protocol::HmiRoadData *msg){
    assert(channel == CVM_CHANNEL_HMI_ROAD_PUB);
    std::shared_ptr<protocol::HmiRoadData> temp_RoadData = std::make_shared<protocol::HmiRoadData>(*msg);
    RoadData.swap(temp_RoadData);

    std::cout<<"signal  Phase  :"<<RoadData->signal_phase<<"\n"
             <<"remain time    :"<<RoadData->remain_time<<"\n"
             <<" Advice        :"<<RoadData->advice<<"\n"
             <<" Advice speed  :"<<RoadData->advice_speed<<"\n";
    std::cout<<"========================================"<<std::endl;
}

void PushHMI::handleLcmHMIEventData(const lcm::ReceiveBuffer *rbuf,
                                    const std::string &channel, const protocol::HmiEventData *msg){
    assert(channel == CVM_CHANNEL_HMI_EVENT_PUB);
    protocol::HmiEventData temp = *msg;
    EventData.insert(std::pair<int32_t, protocol::HmiEventData>(temp.type, temp));
    //std::shared_ptr<protocol::HmiEventData> temp_EventData = std::make_shared<protocol::HmiEventData>(*msg);
//    EventData.swap(temp_EventData);
}
/**
 * @brief PushHMI::handleLcmHMIWarnData
 * @param rbuf
 * @param channel
 * @param msg
 */
void PushHMI::handleLcmHMIWarnData(const lcm::ReceiveBuffer *rbuf,
                                   const std::string &channel, const protocol::HmiWarnData *msg){
    assert(channel == CVM_CHANNEL_HMI_WARN_PUB);
    std::shared_ptr<protocol::HmiWarnData> temp_WarnData = std::make_shared<protocol::HmiWarnData>(*msg);
    WarnData.swap(temp_WarnData);
}

/**
 * @brief PushHMI::sendUdpToHMI
 */
void PushHMI::sendUdpToHMI(){

    //std::cout<<"send to HMI"<<std::endl;

    cJSON* Json_root =NULL;
    Json_root = cJSON_CreateObject();
    if(NULL == Json_root){
        return ;
    }

    cJSON_AddStringToObject(Json_root,"Header","SAIC");
    std::string userid = std::to_string(VehicleData->carId);
    //cJSON_AddStringToObject(Json_root, "UserID", userid.c_str());
    cJSON_AddStringToObject(Json_root, "UserID","555");
    cJSON_AddNumberToObject(Json_root, "RoadType", 1);
    cJSON_AddNumberToObject(Json_root, "Dispalymode", 2);
    cJSON_AddNumberToObject(Json_root, "MapMode", 1);
    cJSON_AddNumberToObject(Json_root, "DSRCMode", 1);
    cJSON_AddNumberToObject(Json_root, "Length", 0);


    cJSON* vehicle_info = updateVehicle_Data();
    if(NULL == vehicle_info){
        cJSON_Delete(Json_root);
        return;
    }
    cJSON_AddItemToObject(Json_root, "Vehicle_Info", vehicle_info);

    cJSON* road_info = updateRoad_Data();
    if(NULL == road_info){
        cJSON_Delete(Json_root);
        return;
    }
    cJSON_AddItemToObject(Json_root, "Road_Info", road_info);

    cJSON* event_info = updateEvent_Data();
    if(NULL == event_info){
        cJSON_Delete(Json_root);
        return;
    }
    cJSON_AddItemToObject(Json_root, "Even_Info", event_info);

    cJSON* warning_info = updateWarning_Data();
    if(NULL == warning_info){
        cJSON_Delete(Json_root);
        return;
    }
    cJSON_AddItemToObject(Json_root, "Warning_Info", warning_info);

    char * p = cJSON_Print(Json_root);
    if(NULL == p)
    {
        cJSON_Delete(Json_root);
        return;
    }

    /// Send Udp Message
    /// printf("%s\n", p);
    if(sendto(hmi_sockfd_, p, strlen(p), 0,(sockaddr*)&hmi_sockaddr_,
              sizeof(sockaddr)) == -1)
    {
        LDIE << "pushhmi send error!";
    }

    cJSON_Delete(Json_root);
    free(p);
}

/**
 * @brief PushHMI::updateVehicle_Data
 * @return dx: ahead dis, dy: left dis
 */
cJSON* PushHMI::updateVehicle_Data(){
    cJSON* Json_vehicle = NULL;
    Json_vehicle = cJSON_CreateObject();
    if(NULL == Json_vehicle){
        return NULL;
    }

    cJSON* HV = NULL;
    HV = cJSON_CreateObject();
    if(NULL == HV){
        cJSON_Delete(Json_vehicle);
        return NULL;
    }
    cJSON_AddBoolToObject(HV, "HostVehicle", true);
    std::string hostid = std::to_string(VehicleData->carId);
    cJSON_AddStringToObject(HV, "ID", hostid.c_str());
    cJSON_AddStringToObject(HV, "Type", "Car");
    cJSON_AddNumberToObject(HV, "dx", 0);
    cJSON_AddNumberToObject(HV, "dy", 0);
    cJSON_AddNumberToObject(HV, "Angel", 0);
    cJSON_AddNumberToObject(HV, "Speed", 0);
    cJSON_AddNumberToObject(HV, "Status", 0);
    cJSON_AddNumberToObject(HV, "attr1", 0);
    cJSON_AddItemToObject(Json_vehicle, "0", HV);

    for(int i = 1; i < 9; i++){
        cJSON* OV = NULL;
        OV = cJSON_CreateObject();
        if(NULL == OV){
            cJSON_Delete(Json_vehicle);
            return NULL;
        }
        cJSON_AddBoolToObject(OV, "HostVehicle", false);
        cJSON_AddStringToObject(OV, "ID", "");
        cJSON_AddStringToObject(OV, "Type", "Car");
        cJSON_AddNumberToObject(OV, "dx", 0);
        cJSON_AddNumberToObject(OV, "dy", 0);
        cJSON_AddNumberToObject(OV, "Angel", 0);
        cJSON_AddNumberToObject(OV, "Speed", 0);
        cJSON_AddNumberToObject(OV, "Status", 0);
        cJSON_AddNumberToObject(OV, "attr1", 0);
        std::string t = std::to_string(i);
        cJSON_AddItemToObject(Json_vehicle, t.c_str(), OV);
    }

    return Json_vehicle;
}

/**
 * @brief PushHMI::updateRoad_Data
 * @return
 */
cJSON* PushHMI::updateRoad_Data(){
    cJSON* Json_road = NULL;
    Json_road = cJSON_CreateObject();
    if(NULL == Json_road){
        return NULL;
    }

    cJSON* mainroad  = NULL;
    mainroad = cJSON_CreateObject();
    if(NULL == mainroad){
        cJSON_Delete(Json_road);
        return NULL;
    }
    cJSON_AddNumberToObject(mainroad, "DeviceID", RoadData->deviceId);
    cJSON_AddNumberToObject(mainroad, "Distance", RoadData->distance);
    cJSON_AddNumberToObject(mainroad, "SignalPhase", RoadData->signal_phase);
    cJSON_AddNumberToObject(mainroad, "RemainTime", RoadData->remain_time);
    cJSON_AddNumberToObject(mainroad, "Advice", RoadData->advice);
    cJSON_AddNumberToObject(mainroad, "AdviceSpeed", RoadData->advice_speed);
    cJSON_AddNumberToObject(mainroad, "att1", 0);
    cJSON_AddItemToObject(Json_road, "0", mainroad);

//    std::cout<<"signal  Phase  :"<<RoadData->signal_phase<<"\n"
//             <<"remain time    :"<<RoadData->remain_time<<"\n"
//             <<" Advice        :"<<RoadData->advice<<"\n"
//             <<" Advice speed  :"<<RoadData->advice_speed<<"\n";
//    std::cout<<"========================================"<<std::endl;

    for(int i = 1; i < 3; i++){
        cJSON* road = NULL;
        road = cJSON_CreateObject();
        if(NULL == road){
            cJSON_Delete(Json_road);
            return NULL;
        }
        cJSON_AddNumberToObject(road, "DeviceID", 0);
        cJSON_AddNumberToObject(road, "Distance", 0);
        cJSON_AddNumberToObject(road, "SignalPhase", 0);
        cJSON_AddNumberToObject(road, "RemainTime", 0);
        cJSON_AddNumberToObject(road, "Advice", 0);
        cJSON_AddNumberToObject(road, "AdviceSpeed", 0);
        cJSON_AddNumberToObject(road, "att1", 0);
        std::string t = std::to_string(i);
        cJSON_AddItemToObject(Json_road, t.c_str(), road);
    }
//    RoadData->deviceId = 0;
//    RoadData->distance = 0;
//    RoadData->signal_phase = 0;
//    RoadData->remain_time = 0;
//    RoadData->advice = 0;
//    RoadData->advice_speed = 0;

    return Json_road;
}

cJSON* PushHMI::updateEvent_Data(){
    cJSON* Json_event = NULL;
    Json_event = cJSON_CreateObject();
    if(NULL == Json_event){
        return NULL;
    }

//    cJSON *mainevent = NULL;
//    mainevent = cJSON_CreateObject();
//    if(NULL == mainevent){
//        return NULL;
//    }
//    cJSON_AddNumberToObject(mainevent, "EventID", EventData->eventId);
//    cJSON_AddNumberToObject(mainevent, "EventName", EventData->name);
//    cJSON_AddNumberToObject(mainevent, "EventType", EventData->type);
//    cJSON_AddNumberToObject(mainevent, "dx1", 0);
//    cJSON_AddNumberToObject(mainevent, "dy1", 0);
//    cJSON_AddNumberToObject(mainevent, "dx2", 0);
//    cJSON_AddNumberToObject(mainevent, "dy2", 0);
//    cJSON_AddNumberToObject(mainevent, "att1", 0);
//    cJSON_AddItemToObject(Json_event, "0", mainevent);
//    if(EventData->eventId!=0)
//        std::cout<<"shou dao xingren "<<"\n"<<
//                   "                 "<<EventData->type<<"\n"
//                   "                 "<<EventData->name<<std::endl;

    int count = 0;
    for (std::map<int32_t, protocol::HmiEventData>::iterator it = EventData.begin();
         it != EventData.end(); ++ it){
        cJSON*event = NULL;
        event = cJSON_CreateObject();
        if(NULL==event){
            cJSON_Delete(Json_event);
            return NULL;
        }
        cJSON_AddNumberToObject(event, "EventID", it->second.eventId);
        cJSON_AddNumberToObject(event, "EventType", it->second.type);
        cJSON_AddNumberToObject(event, "EventName", it->second.name);
        cJSON_AddNumberToObject(event, "dx1", 0);
        cJSON_AddNumberToObject(event, "dy1", 0);
        cJSON_AddNumberToObject(event, "dx2", 0);
        cJSON_AddNumberToObject(event, "dy2", 0);
        cJSON_AddNumberToObject(event, "att1", 0);
        std::string t = std::to_string(count);
        cJSON_AddItemToObject(Json_event, t.c_str(),event);
        count++;
    }
    for (int i = count; i < 6; i++){
        cJSON* event = NULL;
        event = cJSON_CreateObject();
        if(NULL == event){
            cJSON_Delete(Json_event);
            return NULL;
        }
        cJSON_AddNumberToObject(event, "EventID", 0);
        cJSON_AddNumberToObject(event, "EventName", 0);
        cJSON_AddNumberToObject(event, "EventType", 0);
        cJSON_AddNumberToObject(event, "dx1", 0);
        cJSON_AddNumberToObject(event, "dy1", 0);
        cJSON_AddNumberToObject(event, "dx2", 0);
        cJSON_AddNumberToObject(event, "dy2", 0);
        cJSON_AddNumberToObject(event, "att1", 0);
        std::string t = std::to_string(i);
        cJSON_AddItemToObject(Json_event, t.c_str(), event);
    }

    EventData.clear();
    return Json_event;
}

/**
 * @brief PushHMI::updateWarning_Data
 * @return
 */
cJSON* PushHMI::updateWarning_Data(){
    cJSON* Json_warning = NULL;
    Json_warning = cJSON_CreateObject();
    if(NULL == Json_warning){
        return NULL;
    }

    cJSON* mainwarn = NULL;
    mainwarn= cJSON_CreateObject();
    if(NULL == mainwarn){
        cJSON_Delete(Json_warning);
        return NULL;
    }
    std::string warnid = std::to_string(WarnData->warnId);
    cJSON_AddStringToObject(mainwarn, "WarningID", warnid.c_str());
    cJSON_AddNumberToObject(mainwarn, "WarningStr", WarnData->warnStr);
    cJSON_AddNumberToObject(mainwarn, "WarningLevel", WarnData->warnLev);
    cJSON_AddNumberToObject(mainwarn, "att1", 0);
    cJSON_AddItemToObject(Json_warning, "0", mainwarn);

//    std::cout<<"WarnID   :"<<WarnData->warnId<<std::endl;
//    std::cout<<"WarnStr  :"<<WarnData->warnStr<<std::endl;
//    std::cout<<"WarnLev  :"<<WarnData->warnLev<<std::endl;

    for(int i = 1; i < 4; i++){
        cJSON* warn = NULL;
        warn = cJSON_CreateObject();
        if(NULL == warn){
            cJSON_Delete(Json_warning);
            return NULL;
        }
        cJSON_AddStringToObject(warn, "WarningID", "");
        cJSON_AddNumberToObject(warn, "WarningStr", -1);
        cJSON_AddNumberToObject(warn, "WarningLevel", -1);
        cJSON_AddNumberToObject(warn, "att1", 0);
        std::string t = std::to_string(i);
        cJSON_AddItemToObject(Json_warning, t.c_str(), warn);
    }
    WarnData->warnId = -1;
    WarnData->warnStr = -1;
    WarnData->warnLev = -1;
    return Json_warning;
}


}

}

}
