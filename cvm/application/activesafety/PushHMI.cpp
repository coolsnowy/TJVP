#include <cvm/base/Logging.h>
#include <cvm/application/activesafety/PushHMI.h>

#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <assert.h>

namespace cvm {

namespace application {

namespace activesafety {

PushHmi::PushHmi(VehiclesModelPtr vsModel)
    :hmi_ip_("192.168.1.101"),
      hmi_port_(4040),
      debug_ip_("192.168.1.111"),
      debug_port_(23333)
{
    assert(vsModel.get() != NULL);
    vsmodel_ptr_ = vsModel;

    hmi_sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if(hmi_sockfd_ == -1){
        LDIE << "pushhmi socket init error!";
    }

    debug_sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if(debug_sockfd_ == -1){
        LDIE << "pushdebug socket init error!";
    }

    memset(&hmi_sockaddr_, 0, sizeof(sockaddr_in));
    hmi_sockaddr_.sin_family      = AF_INET;
    hmi_sockaddr_.sin_port        = htons(hmi_port_);
    hmi_sockaddr_.sin_addr.s_addr = inet_addr(hmi_ip_.c_str());

    memset(&debug_sockaddr_, 0, sizeof(sockaddr_in));
    debug_sockaddr_.sin_family      = AF_INET;
    debug_sockaddr_.sin_port        = htons(debug_port_);
    debug_sockaddr_.sin_addr.s_addr = inet_addr(debug_ip_.c_str());
}

PushHmi::~PushHmi()
{
    close(hmi_sockfd_);
    close(debug_sockfd_);
}

void PushHmi::sendUdpToHMI(){
    assert(vsmodel_ptr_.get() != NULL);

    if(!vsmodel_ptr_->host_vehicle_)
    {
        return;
    }

    cJSON* Json_root = NULL;
    Json_root = cJSON_CreateObject();
    if(NULL == Json_root){
        return;
    }
    cJSON_AddStringToObject(Json_root, "Header", "SAIC");
    std::string userid = std::to_string(vsmodel_ptr_->host_vehicle_->id);
    cJSON_AddStringToObject(Json_root, "UserID", userid.c_str());
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
    if(sendto(debug_sockfd_, p, strlen(p), 0,(sockaddr*)&debug_sockaddr_,
              sizeof(sockaddr)) == -1)
    {
        LDIE << "pushdebug send error!";
    }

    cJSON_Delete(Json_root);
    free(p);
}

/**
 * @brief PushHmi::updateVehicle_Data
 * @param Json_vehicle
 * @details dx: ahead dis, dy: left dis
 */
cJSON* PushHmi::updateVehicle_Data()
{
    /// Json : Vehicle Info
    ///
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
    std::string hostid = std::to_string(vsmodel_ptr_->host_vehicle_->id);
    cJSON_AddStringToObject(HV, "ID", hostid.c_str());
    cJSON_AddStringToObject(HV, "Type", "Car");
    cJSON_AddNumberToObject(HV, "dx", 0);
    cJSON_AddNumberToObject(HV, "dy", 0);
    cJSON_AddNumberToObject(HV, "Angel", vsmodel_ptr_->host_vehicle_->relativeHeading);
    cJSON_AddNumberToObject(HV, "Speed", vsmodel_ptr_->host_vehicle_->speed);
    // --- out of protocols
    cJSON_AddNumberToObject(HV, "WheelAngle", vsmodel_ptr_->host_vehicle_->wheelAngle);
    // ---
    cJSON_AddNumberToObject(HV, "Status", 0);
    cJSON_AddNumberToObject(HV, "attr1", 1);
    cJSON_AddItemToObject(Json_vehicle, "0", HV);

    int count = 0;
    for (std::map<int, VehiclePtr>::iterator it = vsmodel_ptr_->vehicles_.begin();
         it != vsmodel_ptr_->vehicles_.end(); ++ it)
    {
        ++ count;
        cJSON* OV = NULL;
        OV = cJSON_CreateObject();
        if(NULL == OV){
            cJSON_Delete(Json_vehicle);
            return NULL;
        }
        cJSON_AddBoolToObject(OV, "HostVehicle", false);
        std::string id = std::to_string(it->second->id);
        cJSON_AddStringToObject(OV, "ID", id.c_str());
        cJSON_AddStringToObject(OV, "Type", "Car");
        cJSON_AddNumberToObject(OV, "dx", it->second->relativePoint.x_);
        cJSON_AddNumberToObject(OV, "dy", -it->second->relativePoint.y_);
        cJSON_AddNumberToObject(OV, "Angel", it->second->relativeHeading);
        cJSON_AddNumberToObject(OV, "Speed", it->second->speed);
        // --- out of protocols
        cJSON_AddNumberToObject(OV, "WheelAngle", it->second->wheelAngle);
        //
        cJSON_AddNumberToObject(OV, "Status", 0);
        cJSON_AddNumberToObject(OV, "attr1", 1);
        std::string t = std::to_string(count);
        cJSON_AddItemToObject(Json_vehicle, t.c_str(), OV);
    }

    for(int i = count + 1; i < 9; i++){
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
        // --- out of protocols
        cJSON_AddNumberToObject(OV, "WheelAngle", 0);
        //
        cJSON_AddNumberToObject(OV, "Status", 0);
        cJSON_AddNumberToObject(OV, "attr1", 0);
        std::string t = std::to_string(i);
        cJSON_AddItemToObject(Json_vehicle, t.c_str(), OV);
    }
    return Json_vehicle;
}

/**
 * @brief PushHmi::updateRoad_Data
 * @return
 */
cJSON* PushHmi::updateRoad_Data(){
    /// Json : Road Info
    ///
    cJSON* Json_road = NULL;
    Json_road = cJSON_CreateObject();
    if(NULL == Json_road){
        return NULL;
    }
    for(int i = 0; i < 3; i++){
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
    return Json_road;
}

/**
 * @brief PushHmi::updateEvent_Data
 * @param Json_event
 * @return
 */
cJSON* PushHmi::updateEvent_Data(){
    /// Json : Event Info
    ///
    cJSON* Json_event = NULL;
    Json_event = cJSON_CreateObject();
    if(NULL == Json_event){
        return NULL;
    }

    for (int i = 0; i < 6; i++){
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
    return Json_event;
}

/**
 * @brief PushHmi::updateWarning_Data
 * @param Json_warning
 * @return
 */
cJSON* PushHmi::updateWarning_Data(){
    /// Json : Warning Info
    ///
    cJSON* Json_warning = NULL;
    Json_warning = cJSON_CreateObject();
    if(NULL == Json_warning){
        return NULL;
    }

    int count = 0;
    for (std::map<WARN_STR, detectResult>::iterator it = vsmodel_ptr_->detect_results_.begin();
         it != vsmodel_ptr_->detect_results_.end(); ++ it)
    {
        cJSON* warn = NULL;
        warn = cJSON_CreateObject();
        if(NULL == warn){
            cJSON_Delete(Json_warning);
            return NULL;
        }
        std::string warnid = std::to_string(it->second.id);
        cJSON_AddStringToObject(warn, "WarningID", warnid.c_str());
        cJSON_AddNumberToObject(warn, "WarningStr", it->second.wStr);
        cJSON_AddNumberToObject(warn, "WarningLevel", it->second.wLvl);
        // --- out of protocols
        cJSON_AddNumberToObject(warn, "WarningTTC", it->second.TTC);
        cJSON_AddNumberToObject(warn, "WarningTHW", it->second.THW);
        //
        cJSON_AddNumberToObject(warn, "att1", 0);
        std::string t = std::to_string(count);
        cJSON_AddItemToObject(Json_warning, t.c_str(), warn);
        ++ count;
    }
    for(int i = count; i < 4; i++){
        cJSON* warn = NULL;
        warn = cJSON_CreateObject();
        if(NULL == warn){
            cJSON_Delete(Json_warning);
            return NULL;
        }
        cJSON_AddStringToObject(warn, "WarningID", "");
        cJSON_AddNumberToObject(warn, "WarningStr", 0);
        cJSON_AddNumberToObject(warn, "WarningLevel", -1);
        // --- out of protocols
        cJSON_AddNumberToObject(warn, "WarningTTC", 0);
        cJSON_AddNumberToObject(warn, "WarningTHW", 0);
        //
        cJSON_AddNumberToObject(warn, "att1", 0);
        std::string t = std::to_string(i);
        cJSON_AddItemToObject(Json_warning, t.c_str(), warn);
    }
    return Json_warning;
}

}

}

}

