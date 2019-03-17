#include <iostream>
#include <math.h>

#include <cvm/base/Logging.h>
#include <cvm/application/activesafety/CollisionDetec.h>
#include <cvm/application/activesafety/ComputeTools.h>

namespace cvm {

namespace application {

namespace activesafety {

Vehicle::Vehicle(const protocol::VehicleData &vdata)
    : id(vdata.carId),
      longitude(vdata.location.longitude),
      latitude(vdata.location.latitude),
      altitude(vdata.location.altitude),
      speed(vdata.speed),
      heading(vdata.azimuth),
      wheelAngle(vdata.steeringWheelAngle),
      relativePoint({vdata.relativeX, vdata.relativeY}),
      relativeHeading(vdata.relativeAzimuth),
      vehicleWidth(1.551),
      vehicleLength(3.569),
      vehicleWheelDis(2.569)
{
    turnLight = ( (vdata.turnLight == 0)?TURN_NONE
                                       :(vdata.turnLight == 1)?TURN_RIGHT:TURN_LEFT );
}

void Vehicle::calPrePath()
{
    predictPath(relativePoint, relativeHeading, wheelAngle,
                speed, vehicleWidth, vehicleLength,
                vehicleWheelDis, prePath);
}


/// -------------------------- split line --------------------------------


bool isDangerPossible(const Vehicle& HV, const Vehicle& OV)
{
    double dis = disOfPoints(HV.relativePoint.x_, HV.relativePoint.y_,
                             OV.relativePoint.x_, OV.relativePoint.y_);
    if(HV.speed > isDanger_hv_speed_low_ && dis < isDanger_ov_area_r_high_)
        return true;
    else
        return false;
}

VEHICLE_LOC calVehicleLocation(const Vehicle& HV, const Vehicle& OV)
{
    if(HV.wheelAngle > calLoc_hv_wheelangle_high_
            || HV.wheelAngle < calLoc_hv_wheelangle_low_)
        return LOC_DEFAULT;

    double x = OV.relativePoint.x_;
    double y = OV.relativePoint.y_;

    if(x < -HV.vehicleWidth){
        return (y >= 0) ? FRONT_LEFT_LOC : BACK_LEFT_LOC;
    }else if(x > HV.vehicleWidth){
        return (y >= 0) ? FRONT_RIGHT_LOC : BACK_RIGHT_LOC;
    }else{
        return (y >= 0) ? FRONT_DIRECT_LOC : BACK_DIRECT_LOC;
    }

}

void calPrePathIntersect(const Vehicle& HV, const Vehicle& OV,
                         detectResult& result,int decType)
{
    double HV_arrowlen = disOfPoints(0, 0, HV.vehicleWidth, HV.vehicleLength);
    double OV_arrowlen = disOfPoints(0, 0, OV.vehicleWidth, OV.vehicleLength);
    double safeDis = 0.5 * HV_arrowlen + 0.5 * OV_arrowlen;
    double HV_interval = HV_arrowlen / HV.speed;
    double OV_interval = OV_arrowlen / OV.speed;

    if(decType == CIRCLETRACK){
        for(int i = 0; i < HV.prePath.size(); ++ i){
            for(int j = 0; j < OV.prePath.size(); ++ j){
                point a = HV.prePath[i];
                point b = OV.prePath[j];
                if(disOfPoints(a.x_, a.y_, b.x_, b.y_) < safeDis){
                    result.isIntersect = true;
                    result.TTC = i * HV_interval;
                    result.THW = fabs(i * HV_interval - j * OV_interval);
                    if(result.THW <2){
                        result.wLvl = HIGH_LVL;
                    }
                    else if(result.THW >=2 && result.THW<5)
                        result.wLvl = MEDIUM_LVL;
                    else
                        result.wLvl = LOW_LVL;
                    return ;
                }
            }
        }
    }
    else if(decType == RECTANGLETRACK ){
        double critical_x = (HV.vehicleWidth+OV.vehicleWidth)/2;
        double critical_y = (HV.vehicleLength+OV.vehicleLength)/2;
        point a;
        point b;
        for(int i=0;i<HV.prePath.size();++i){
            for(int j=0;j<OV.prePath.size();++j){
                a = HV.prePath[i];
                b = OV.prePath[j];
                if(fabs(a.x_ - b.x_)<critical_x && fabs(a.y_-b.y_)<critical_y){
                    result.isIntersect = true;
                    result.TTC = i*HV_interval;
                    result.THW = fabs(i * HV_interval - j * OV_interval);
                    if(result.THW <2){
                        result.wLvl = HIGH_LVL;
                    }
                    else if(result.THW >=2 && result.THW<5)
                        result.wLvl = MEDIUM_LVL;
                    else
                        result.wLvl = LOW_LVL;
                    return ;
                }
            }
        }
    }
    result.isIntersect = false;
}


///------------------------------ split line ---------------------------------

/**
 * @brief is_DNPW_Warning
 * @param HV   host vehicle
 * @param OV   vehicle on near left lane with reverse heading
 * @param OV1  vehicle in front of HV with same heading
 * @param result
 */
void is_DNPW_Warning(const Vehicle& HV, const Vehicle& OV,
                     std::map<WARN_PRIO, detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};
    calPrePathIntersect(HV, OV, rlt,RECTANGLETRACK);
    if(rlt.isIntersect){
        rlt.id = OV.id;
        rlt.wStr = DONOTPASS_WARNING;
        rlt.wPrio = HIGH_PRIO;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}

/**
 * @brief left side intersect collision
 * @param HV   host vehicle on the main lane
 * @param OV   vehicle on cross lane
 * @param result
 */
void is_L_ICW_Warning(const Vehicle& HV, const Vehicle& OV,
                    std::map<WARN_PRIO, detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};
    calPrePathIntersect(HV, OV, rlt,CIRCLETRACK);
    if(rlt.isIntersect)
    {
        rlt.id = OV.id;
        rlt.wStr = INTERSECT_WARNING_L;
        rlt.wPrio = MEDIUM_PRIO;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}

/**
 * @brief right side intersect collision
 * @param HV : host vehicle on the reverse lane
 * @param OV : other vehicle on the cross lane
 * @param result
 */
void is_R_ICW_Warning(const Vehicle& HV, const Vehicle& OV,
                    std::map<WARN_PRIO, detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};
    calPrePathIntersect(HV, OV, rlt,CIRCLETRACK);
    if(rlt.isIntersect)
    {
        rlt.id = OV.id;
        rlt.wStr = INTERSECT_WARNING_R;
        rlt.wPrio = MEDIUM_PRIO;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}
void is_L_PW_Warning(const Vehicle& HV, const Vehicle& OV,
                      std::map<WARN_PRIO, detectResult>& result){
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};
    if(OV.speed > HV.speed+isPW_dis_speed ){
        rlt.isIntersect = true;
        rlt.id = OV.id;
        rlt.wStr = PASSINGBY_WARNING_L;
        rlt.wPrio = MEDIUM_PRIO;
        rlt.wLvl = MEDIUM_LVL;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}

void is_R_PW_Warning(const Vehicle& HV, const Vehicle& OV,
                      std::map<WARN_PRIO, detectResult>& result){
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};
    if(OV.speed > HV.speed+isPW_dis_speed ){
        rlt.isIntersect = true;
        rlt.id = OV.id;
        rlt.wStr = PASSINGBY_WARNING_R;
        rlt.wPrio = MEDIUM_PRIO;
        rlt.wLvl = MEDIUM_LVL;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}

void is_L_LCW_Warning(const Vehicle& HV, const Vehicle& OV,
                   std::map<WARN_PRIO, detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};

    calPrePathIntersect(HV,OV,rlt,RECTANGLETRACK);

    if(HV.turnLight == TURN_LEFT && rlt.isIntersect){
        rlt.id = OV.id;
        rlt.wStr = LINECHANGE_WARNING_L; // the trueth is LINECHANGE_WARNING_L
        rlt.wPrio = MEDIUM_PRIO;
        result.insert(std::pair<WARN_PRIO,detectResult>(rlt.wPrio,rlt));
    }
    else if(OV.relativePoint.x_ > -isLCW_dis_x_max && OV.relativePoint.x_<-isLCW_dis_x_max &&
            OV.relativePoint.y_ >-isLCW_dis_y_max && OV.relativePoint.y_ <-isLCW_dis_y_min){
        rlt.id = OV.id;
        rlt.wStr = PASSINGBY_WARNING_L;//LINECHANGE_WARNING_L;
        rlt.wPrio = LOW_PRIO;
        rlt.wLvl = LOW_LVL;
        result.insert(std::pair<WARN_PRIO,detectResult>(rlt.wPrio,rlt));
    }
}

void is_R_LCW_Warning(const Vehicle& HV, const Vehicle& OV,
                   std::map<WARN_PRIO, detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};

    calPrePathIntersect(HV,OV,rlt,RECTANGLETRACK);

    if(HV.turnLight == TURN_RIGHT && rlt.isIntersect){
        rlt.id = OV.id;
        rlt.wStr = LINECHANGE_WARNING_R; //LINECHANGE_WARNING_R;
        rlt.wPrio = MEDIUM_PRIO;
        result.insert(std::pair<WARN_PRIO,detectResult>(rlt.wPrio,rlt));
    }
    else if(OV.relativePoint.x_ < isLCW_dis_x_max && OV.relativePoint.x_ > isLCW_dis_x_max &&
            OV.relativePoint.y_ >-isLCW_dis_y_max && OV.relativePoint.y_ <-isLCW_dis_y_min){
        rlt.id = OV.id;
        rlt.wStr = PASSINGBY_WARNING_R; //LINECHANGE_WARNING_R;
        rlt.wPrio = LOW_PRIO;
        rlt.wLvl = LOW_LVL;
        result.insert(std::pair<WARN_PRIO,detectResult>(rlt.wPrio,rlt));
    }
}

void is_INCM_Warning(const Vehicle& HV, const Vehicle& OV,
                    std::map<WARN_PRIO, detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT, PRIO_DEFAULT, LVL_DEFAULT,
                        false, -1, -1, 0};
    calPrePathIntersect(HV, OV, rlt,RECTANGLETRACK);
//    if(OV.relativePoint.y_ > isINCM_ov_area_y_low_
//            && rlt.isIntersect)
    if(rlt.isIntersect)
    {
        rlt.id = OV.id;
        rlt.wStr = INCOMING_WARNING;
        rlt.wPrio = MEDIUM_PRIO;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}

void is_FCW_Warning(const Vehicle& HV, const Vehicle& OV, std::map<WARN_PRIO,detectResult>& result)
{
    detectResult rlt = {-1, STR_DEFAULT,PRIO_DEFAULT,LVL_DEFAULT,
                        false, -1, -1, 0};
    calPrePathIntersect(HV, OV, rlt, RECTANGLETRACK);
    if(rlt.isIntersect && HV.speed>OV.speed+isFCW_dis_speed){
        rlt.id = OV.id;
        rlt.wStr = FCW_WARNING;
        rlt.wPrio = MEDIUM_PRIO;
        rlt.wLvl = MEDIUM_LVL;
        result.insert(std::pair<WARN_PRIO, detectResult>(rlt.wPrio, rlt));
    }
}


///------------------------------ split line ---------------------------------

/**
 * @brief
 */
void mostDangerV_V(const detectResult &detc, protocol::HmiWarnData& tHW){

    tHW.warnId = detc.id;
    tHW.warnStr = detc.wStr;
    tHW.warnLev = detc.wLvl;

}


VehiclesModel::VehiclesModel(lcm::LCM &lcm)
    :lcm_(lcm),
     liveTimeCount(0)
{

}

void VehiclesModel::log_result()
{
    std::cout << "=================================================" << std::endl;
    std::cout << "Host Vehicle: " << host_vehicle_->id << std::endl;
    for(auto it = vehicles_.begin();
        it != vehicles_.end(); ++ it)
    {
        std::cout << "Other Vehicle: " << it->first << std::endl;
    }

    std::cout << "-- six grids --" << std::endl;
    for(auto it = six_grids_state_.begin();
        it != six_grids_state_.end(); ++ it)
    {
        std::cout << "LOC: " << it->first << std::endl;
        for(auto it2 = it->second.begin();
            it2 != it->second.end(); ++ it2)
        {
            std::cout << "ID: " << it2->second
                   << ", Status: "
                   << ((it2->first == SAME_DIRECT) ? "SAME_DIRECT"
                      : (it2->first == REVERSE_DIRECT) ? "REVERSE_DIRECT"
                      : "INTERSECT_DIRECT") << std::endl;
        }
    }

    std::cout << "-- warn result --" << std::endl;
    for(auto it = detect_results_.begin();
        it != detect_results_.end(); ++ it){
        std::cout << "ID: " << it->second.id
               << ", Warn_Str: "
               << ( (it->first == INTERSECT_WARNING_L) ? "INTERSECT_WARNING_L"
                  : (it->first == INTERSECT_WARNING_R) ? "INTERSECT_WARNING_R"
                  : (it->first == DONOTPASS_WARNING) ? "DONOTPASS_WARNING"
                  : (it->first == LINECHANGE_WARNING_L) ? "LINECHANGE_WARNING_L"
                  : (it->first == LINECHANGE_WARNING_R) ? "LINECHANGE_WARNING_R"
                  : (it->first == INCOMING_WARNING) ? "INCOMING_WARNING"
                  : "PEDESTRIANS")<< std::endl;
                  //: "INCOMING_WARNING") << std::endl;
    }

    std::cout << "=================================================" << std::endl;
}

/**
 * @brief Vehicles::dangerResultFusionAndOutput
 */
void VehiclesModel::dangerResultFusionAndOutput()
{
    six_grids_state_.clear();
    if(!host_vehicle_ || vehicles_.size() == 0){
        LDEBUG << "Vehicles nums don't meet the requirement."
               << "(HostVehicle = " << (host_vehicle_?"true":"false")
               << ", OtherVehicle = " << vehicles_.size() << ")";
        return;
    }

    std::map<int, VehiclePtr>::iterator iter = vehicles_.begin();
    for(; iter != vehicles_.end(); ++ iter){
        sixGridsDetect(*host_vehicle_, *(iter->second));
    }
    //if(six_grids_state_.size() == 0) return;


    /// result detect and fusion
    /// need to modify and should be given more attention
    std::map<WARN_PRIO, detectResult> last_detect_results(detect_results_);
    detect_results_.clear();
    vehicleDangerDetection();

    if(last_detect_results.size() != 0
            && detect_results_.size() == 0
            && liveTimeCount < DETECTRESULTS_TTL)
    {
        detect_results_ = last_detect_results;
        ++ liveTimeCount;
    }
    else{
        liveTimeCount = 0;
    }

    // push the most dangerous to HMI
    protocol::HmiWarnData tHW = protocol::HmiWarnData{STR_DEFAULT, PRIO_DEFAULT,LVL_DEFAULT};
    std::map<WARN_PRIO, detectResult>::iterator iter_w;
    iter_w = detect_results_.find(HIGH_PRIO);
    if( iter_w!=detect_results_.end() ){
        mostDangerV_V(iter_w->second, tHW);
        lcm_.publish(CVM_CHANNEL_HMI_WARN_PUB, &tHW);
    }
    else{
        iter_w = detect_results_.find(MEDIUM_PRIO);
        if( iter_w!=detect_results_.end() ){
            mostDangerV_V(iter_w->second, tHW);
            lcm_.publish(CVM_CHANNEL_HMI_WARN_PUB, &tHW);
        }
        else{
            iter_w = detect_results_.find(LOW_PRIO);
            if( iter_w!=detect_results_.end() ){
                mostDangerV_V(iter_w->second, tHW);
                lcm_.publish(CVM_CHANNEL_HMI_WARN_PUB, &tHW);
            }
            else
                lcm_.publish(CVM_CHANNEL_HMI_WARN_PUB, &tHW);
        }
    }

    /// LOG
    log_result();
}

/**
 * @brief Vehicles::vehicleDangerDetection
 */
void VehiclesModel::vehicleDangerDetection()
{
    std::map<VEHICLE_STATUS, int> &FL_LOC_VEHICLE_MAP = six_grids_state_[FRONT_LEFT_LOC];
    std::map<VEHICLE_STATUS, int> &FR_LOC_VEHICLE_MAP = six_grids_state_[FRONT_RIGHT_LOC];
    std::map<VEHICLE_STATUS, int> &FD_LOC_VEHICLE_MAP = six_grids_state_[FRONT_DIRECT_LOC];
    std::map<VEHICLE_STATUS, int> &BL_LOC_VEHICLE_MAP = six_grids_state_[BACK_LEFT_LOC];
    std::map<VEHICLE_STATUS, int> &BR_LOC_VEHICLE_MAP = six_grids_state_[BACK_RIGHT_LOC];

    /// assume that there is only one vehicle in each location
    /// FL BLOCK:
    // Reverse Direction
    if(FL_LOC_VEHICLE_MAP.find(REVERSE_DIRECT) != FL_LOC_VEHICLE_MAP.end())
    {
        Vehicle& OV = *vehicles_[FL_LOC_VEHICLE_MAP[REVERSE_DIRECT]];
        double dis = disOfPoints(host_vehicle_->relativePoint.x_,host_vehicle_->relativePoint.y_,
                                 OV.relativePoint.x_, OV.relativePoint.y_);
        if( host_vehicle_->turnLight == TURN_LEFT && dis > 15)
            is_DNPW_Warning(*host_vehicle_, OV, detect_results_);
        else
            is_INCM_Warning(*host_vehicle_, OV, detect_results_);
    }
    // Intersection
    if(FL_LOC_VEHICLE_MAP.find(INTERSECT_DIRECT) != FL_LOC_VEHICLE_MAP.end())
    {
        Vehicle& OV = *vehicles_[FL_LOC_VEHICLE_MAP[INTERSECT_DIRECT]];
        is_L_ICW_Warning(*host_vehicle_, OV, detect_results_);
    }

    /// FD BLOCK:
    // Reverse Dircection
    if(FD_LOC_VEHICLE_MAP.find(REVERSE_DIRECT) != FD_LOC_VEHICLE_MAP.end())
    {
        Vehicle& OV = *vehicles_[FD_LOC_VEHICLE_MAP[REVERSE_DIRECT]];
        double dis = disOfPoints(host_vehicle_->relativePoint.x_,host_vehicle_->relativePoint.y_,
                                 OV.relativePoint.x_, OV.relativePoint.y_);
        if( host_vehicle_->turnLight == TURN_LEFT && dis > 15 )
            is_DNPW_Warning(*host_vehicle_, OV,detect_results_);
        else
            is_INCM_Warning(*host_vehicle_, OV, detect_results_);
    }
    // Same Direction
    if(FD_LOC_VEHICLE_MAP.find(SAME_DIRECT)!=FD_LOC_VEHICLE_MAP.end()){
        Vehicle& OV = *vehicles_[FD_LOC_VEHICLE_MAP[SAME_DIRECT]];
        is_FCW_Warning(*host_vehicle_, OV, detect_results_);
    }

    /// FR BLOCK
    // Intersection
    if(FR_LOC_VEHICLE_MAP.find(INTERSECT_DIRECT) != FR_LOC_VEHICLE_MAP.end())
    {
        Vehicle& OV = *vehicles_[FR_LOC_VEHICLE_MAP[INTERSECT_DIRECT]];
        is_R_ICW_Warning(*host_vehicle_, OV, detect_results_);
    }

    ///BL BLOCK
    if(BL_LOC_VEHICLE_MAP.find(SAME_DIRECT) != BL_LOC_VEHICLE_MAP.end())
    {
        Vehicle& OV = *vehicles_[BL_LOC_VEHICLE_MAP[SAME_DIRECT]];
        if(host_vehicle_->turnLight == TURN_LEFT)
            is_L_LCW_Warning(*host_vehicle_, OV, detect_results_);
        else
            is_L_PW_Warning(*host_vehicle_, OV, detect_results_);
    }

    /// BR BLOCK
    if(BR_LOC_VEHICLE_MAP.find(SAME_DIRECT) != BR_LOC_VEHICLE_MAP.end())
    {
        Vehicle& OV = *vehicles_[BR_LOC_VEHICLE_MAP[SAME_DIRECT]];

        if(host_vehicle_->turnLight == TURN_RIGHT)
            is_R_LCW_Warning(*host_vehicle_, OV, detect_results_);
        else
            is_R_PW_Warning(*host_vehicle_, OV, detect_results_);
    }
}

/**
 * @brief Vehicles::sixGridsDetect
 * @param HV
 * @param OV
 */
void VehiclesModel::sixGridsDetect(const Vehicle &HV, const Vehicle &OV)
{
    /// recognise Danger is possible
    if(isDangerPossible(HV, OV) == false){
        return;
    }

    /// recognise vehicle status in different location
    switch(calVehicleLocation(HV, OV))
    {
    case LOC_DEFAULT:break;
    case FRONT_LEFT_LOC:
        if(OV.relativeHeading < FL_REVERSE_DIR_ov_heading_high_
                && OV.relativeHeading > FL_REVERSE_DIR_ov_heading_low_
                && OV.relativePoint.x_ > FL_REVERSE_DIR_ov_area_x_low_)
        {
            /// front_left: REVERSE_DIRECT
            six_grids_state_[FRONT_LEFT_LOC].insert(
                            std::pair<VEHICLE_STATUS, int>(REVERSE_DIRECT, OV.id));
        }
        else if(OV.relativeHeading > FL_INTERSECT_DIR_ov_heading_low_
                && OV.relativeHeading < FL_INTERSECT_DIR_ov_heading_high_)
        {
            /// front_left: INTERSECT_DIRECT
            six_grids_state_[FRONT_LEFT_LOC].insert(
                        std::pair<VEHICLE_STATUS, int>(INTERSECT_DIRECT, OV.id));
        }
        break;
    case FRONT_DIRECT_LOC:
        if(OV.relativeHeading > FD_SAME_DIR_ov_heading_low_
                && OV.relativeHeading < FD_SAME_DIR_ov_heading_high_)
        {
            /// front_direct: SAME_DIRECT
            six_grids_state_[FRONT_DIRECT_LOC].insert(
                        std::pair<VEHICLE_STATUS, int>(SAME_DIRECT, OV.id));
        }
        else if(OV.relativeHeading > FD_REVERSE_DIR_ov_heading_low_
                && OV.relativeHeading < FD_REVERSE_DIR_ov_heading_high_)
        {
            /// front_direct: REVERSE_DIRECT
            six_grids_state_[FRONT_DIRECT_LOC].insert(
                        std::pair<VEHICLE_STATUS, int>(REVERSE_DIRECT, OV.id));
        }
        break;
    case FRONT_RIGHT_LOC:
        if(OV.relativeHeading > FR_INTERSECT_DIR_ov_heading_low_
                || OV.relativeHeading < FR_INTERSECT_DIR_ov_heading_high_)
        {
            /// front_right: INTERSECT_DIRECT
            six_grids_state_[FRONT_RIGHT_LOC].insert(
                        std::pair<VEHICLE_STATUS, int>(INTERSECT_DIRECT, OV.id));
        }
        break;
    case BACK_LEFT_LOC:
        if(OV.relativeHeading > BL_SAME_DIR_ov_heading_low_
                && OV.relativeHeading < BL_SAME_DIR_ov_heading_high_)
        {
            /// back_left: SAME_DIRECT
            six_grids_state_[BACK_LEFT_LOC].insert(
                        std::pair<VEHICLE_STATUS, int>(SAME_DIRECT, OV.id));
        }
        break;
    case BACK_DIRECT_LOC:
        break;
    case BACK_RIGHT_LOC:
        if(OV.relativeHeading > BR_SAME_DIR_ov_heading_low_
                && OV.relativeHeading < BR_SAME_DIR_ov_heading_high_)
        {
            /// back_right: SAME_DIRECT
            six_grids_state_[BACK_RIGHT_LOC].insert(
                        std::pair<VEHICLE_STATUS, int>(SAME_DIRECT, OV.id));
        }
        break;
    default:break;
    }
}


///------------------------- split line ------------------------------

/**
 * @brief Vehicles::refreshVehicle
 * @param vdata
 * @param isHost
 */
void VehiclesModel::refreshVehicle(const protocol::VehicleData &vdata, bool isHost)
{
    /// Not thread safe
    VehiclePtr tVptr = std::make_shared<Vehicle>(vdata);
    tVptr->calPrePath();
    if(isHost){
        host_vehicle_.swap(tVptr);
//        LINFO << "===================================";
//        LINFO << "New host vehicle: " << vdata.carId;
//        LINFO << "===================================";
//        LINFO << " ";
        protocol::HmiVehicleData thd;
        thd.HostVehicle = true;
        thd.carId = host_vehicle_->id;
        thd.dx = 0;
        thd.dy = 0;
        thd.speed = host_vehicle_->speed;
        thd.heading = host_vehicle_->heading;
        thd.status = 3;
        lcm_.publish(CVM_CHANNEL_HMI_VEHICLE_PUB, &thd);
        //std::cout<<" safety push success!"<<std::endl;
    }
    else{
        vehicles_[vdata.carId].swap(tVptr);
//        LINFO << "===================================";
//        LINFO << "New other vehicle: " << vdata.carId;
//        LINFO << "===================================";
//        LINFO << " ";
//        LDEBUG << "Vehicle Size = " << vehicles_.size();
    }
}

/**
 * @brief Vehicles::removeVehicle
 * @param vdata
 */
void VehiclesModel::removeVehicle(const protocol::VehicleCtrlData &vdata)
{
    auto rm_it = vehicles_.find(vdata.carId);
    if(rm_it != vehicles_.end())
    {
        vehicles_.erase(rm_it);
        LDEBUG << "Delete vehicle: " << vdata.carId;
    }
}


}

}

}

