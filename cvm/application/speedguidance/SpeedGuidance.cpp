#include <cvm/application/speedguidance/SpeedGuidance.h>
#include <math.h>


namespace cvm {

namespace application {

namespace speedguidance {

SpeedGuidance::SpeedGuidance(const SpeedGuidanceConfig& config)
    :_loop("speedguidance"),
      dis_car_inter(0),
     _config(config)
{
    if(!_config.debug){
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Info,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush,&*_logger,std::placeholders::_1));
    }else{
        base::Logging::setLogLevel(base::Logging::Debug);
    }

    if(!_lcm.good()){
        LDIE<<"lcm init error";
    }

    this_vehicle.reset(new protocol::VehicleData);
    drive_lane.straightState = 0;

    _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_INTERSECTION_PUB, &SpeedGuidance::handleLcmReadSPAT,this);
    _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB, &SpeedGuidance::handleLcmReadThisVehicle,this);

    _lcmChannel.reset(new base::Channel(&_loop, _lcm.getFileno(), "lcm"));
    _lcmChannel->setReadCallback(std::bind(&lcm::LCM::handle, &_lcm));
    _lcmChannel->enableReading();

    _loop.runEvery(100,[&](){ SpeedGuidance::cal_adv_speed();});

    LINFO<<"Loop start";

}

SpeedGuidance::~SpeedGuidance(){
    _lcmChannel->remove();
    LINFO<<"Loop end";
}

void SpeedGuidance::loop(){
    _loop.loop();
}

/**
 * @brief to get spat message
 * @param rbuf
 * @param channel
 * @param msg
 */
void SpeedGuidance::handleLcmReadSPAT(const lcm::ReceiveBuffer *rbuf,const std::string &channel,
                                      const protocol::IntersectionData *msg){
    assert(channel == CVM_CHANNEL_WORLDMODEL_INTERSECTION_PUB);
    Intersections_.push_back(*msg);

    std::cout<<"inter numbe: "<<msg->intersectionId<<std::endl;
//    transformGPStoRS(this_vehicle->location.latitude,this_vehicle->location.longitude,
//                     msg->refPoint.latitude,msg->refPoint.longitude,this_vehicle->azimuth);
//    std::cout<<"        lane1: "<<std::endl;
//    transformGPStoRS(this_vehicle->location.latitude,this_vehicle->location.longitude,
//                     msg->lanes[0].refPoint.latitude,msg->lanes[0].refPoint.longitude,this_vehicle->azimuth);
//    std::cout<<"        lane2: "<<std::endl;
//    transformGPStoRS(this_vehicle->location.latitude,this_vehicle->location.longitude,
//                     msg->lanes[1].refPoint.latitude,msg->lanes[1].refPoint.longitude,this_vehicle->azimuth);
//    std::cout<<"        lane3: "<<std::endl;
//    transformGPStoRS(this_vehicle->location.latitude,this_vehicle->location.longitude,
//                     msg->lanes[2].refPoint.latitude,msg->lanes[2].refPoint.longitude,this_vehicle->azimuth);
//    std::cout<<"==============================="<<std::endl;
}

/**
 * @brief get this vehicle data
 * @param rbuf
 * @param channel
 */
void SpeedGuidance::handleLcmReadThisVehicle(const lcm::ReceiveBuffer* rbuf, const std::string& channel,
                                             const protocol::VehicleData *msg){
    assert(channel == CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB);
    VehiclePtr temp_vData = std::make_shared<protocol::VehicleData>(*msg);
    this_vehicle.swap(temp_vData);
}

/**
 * @brief to get the latest intersection & match-lanes
 */
void SpeedGuidance::choose_light(){

    double self_lat = this_vehicle->location.latitude;
    double self_long = this_vehicle->location.longitude;
    double heading = this_vehicle->azimuth;
    VectorPP relative_I;
    VectorPP relative_A ;
    bool getapp = false;
    double latest_inter = 200;
    double latest_app = 200;
    protocol::Lane best_match;

//    std::cout<<Intersections_.size()<<std::endl;
//    if(Intersections_.size() == 0){
//        std::cout<<" no intersection in the front"<<std::endl;
//        drive_lane.approachId = 0;
//        drive_lane.straightState = 0;
//        return ;
//    }
    for(auto it = Intersections_.begin();it != Intersections_.end();++it){
        transformGPStoRS(self_lat,self_long,it->refPoint.latitude,it->refPoint.longitude,heading,relative_I);
        if( abs(relative_I.x)< 15 && relative_I.y>0 && relative_I.y<latest_inter+10){
            latest_inter = relative_I.y;
            for(auto itapp = it->lanes.begin(); itapp!=it->lanes.end();++itapp){
                transformGPStoRS(self_lat,self_long,itapp->refPoint.latitude,
                                              itapp->refPoint.longitude,heading, relative_A);
                if(fabs(relative_A.x)<5 && relative_A.y<latest_app){
                    latest_app = relative_A.y;
                    best_match = *itapp;
                }
            }
            drive_lane = best_match;
            Inter_position.x = relative_I.x;
            Inter_position.y = relative_I.y;
//            dis_car_inter = cal_dis_of_GPS(this_vehicle->location.latitude, this_vehicle->location.longitude,
//                                           best_match.refPoint.latitude, best_match.refPoint.longitude);
        }
        else{
            std::cout<<it->intersectionId<<"  is not interested! "<<std::endl;
            std::cout<<"         the center point:x ="<<relative_I.x<<"  y= "<<relative_I.y<<std::endl;
            std::cout<<"         the latest inter :"<<latest_inter<<std::endl;

            drive_lane.approachId = 0;
            drive_lane.straightState = 0;
            dis_car_inter = 0;
            Inter_position.x = 0;
            Inter_position.y = 0;
        }
    }
}

void SpeedGuidance::cal_adv_speed(){

    double limit_speed = 50;
    double min_speed = 0;
    double max_speed = 0;
    double diff_speed = 0;
    double current_speed = this_vehicle->speed*3.6;
    // ID, distance, phase, remain time, advice, advice speed
    protocol::HmiRoadData temp_RoadData = {0,0,SIGNAL_DEFAULT,0,0,0};
    // ID, name, type, x1,y1,x2,y2
    protocol::HmiEventData temp_EventData = {0,0,0,0,0,0,0};

    // overspeed
    if( current_speed > limit_speed){
        temp_EventData.eventId = this_vehicle->carId;
        temp_EventData.type = 2;
        temp_EventData.name = 3;
        _lcm.publish(CVM_CHANNEL_HMI_EVENT_PUB, &temp_EventData);
    }

    choose_light();

    VectorPP relative_A ;
    double self_lat = this_vehicle->location.latitude;
    double self_long = this_vehicle->location.longitude;

    transformGPStoRS(self_lat,self_long,drive_lane.refPoint.latitude,drive_lane.refPoint.longitude,
                     this_vehicle->azimuth,relative_A);

    if(drive_lane.approachId == 2){
        relative_A.y +=16;
    }
    else if(drive_lane.approachId ==3){
        relative_A.y-=18;
    }
    dis_car_inter = sqrt(relative_A.x*relative_A.x+relative_A.y*relative_A.y);

    // Running through the red light
    if(drive_lane.straightState == REDLIGHT ){
        if( Inter_position.y>0 && relative_A.y<0 &&  relative_A.y>-8 &&current_speed>3){
            temp_EventData.eventId = this_vehicle->carId;
            temp_EventData.type = 2;
            temp_EventData.name = 1;
            _lcm.publish(CVM_CHANNEL_HMI_EVENT_PUB, &temp_EventData);
        }
        std::cout<<drive_lane.approachId<<std::endl;
        std::cout<<"intersection:"<<Inter_position.x<< "   "<<Inter_position.y<<std::endl;
        std::cout<<"approach    :"<<relative_A.x<<"   "<<relative_A.y<<std::endl;
        std::cout<<"current speed :"<<current_speed<<std::endl;
        std::cout<<"Event type  : type"<<temp_EventData.type<<"   name:"<<temp_EventData.name<<std::endl;
    }

    std::cout<<"==============Speed Guidance==============="<<std::endl;

    if(drive_lane.straightState == SIGNAL_DEFAULT){
        _lcm.publish(CVM_CHANNEL_HMI_ROAD_PUB, &temp_RoadData);
        return ;
    }
    else{
        temp_RoadData.deviceId = drive_lane.approachId;
        temp_RoadData.signal_phase = drive_lane.straightState;
        temp_RoadData.remain_time = drive_lane.straightTimeToChange;


        if(drive_lane.straightState == GREENLIGHT){
            min_speed = 3.6*dis_car_inter/drive_lane.straightTimeToChange;
            if( min_speed >limit_speed && dis_car_inter<=70){
                temp_RoadData.advice = 0; // advice: stop the car
                //temp_RoadData.advice_speed = 0;
            }
            else if(min_speed>limit_speed && dis_car_inter>70){
                temp_RoadData.advice = 1;  // advice : keep the speed
                temp_RoadData.advice_speed = current_speed;
            }
            else{
                temp_RoadData.advice_speed = (min_speed+limit_speed)/2;
                if(current_speed>min_speed && current_speed<limit_speed){
                    temp_RoadData.advice = 1; // advice : keep the speed
                    temp_RoadData.advice_speed = current_speed;
                }
                else if(current_speed<=min_speed){
                    diff_speed = fabs(temp_RoadData.advice_speed - current_speed);
                    if( diff_speed < 10)
                        temp_RoadData.advice = 2; // advice :  speed up softly
                    else
                        temp_RoadData.advice = 3; // advice : speed up rapidly
                }
                else if(current_speed >= limit_speed){
                    diff_speed = fabs(temp_RoadData.advice_speed - current_speed);
                    if(diff_speed<10)
                        temp_RoadData.advice = 4; // advice : slow down softly
                    else
                        temp_RoadData.advice =5; // advice : slow down repidly
                }
            }
        }
        else
        {
            if(drive_lane.straightState == YELLOWLIGHT){

                min_speed = 3.6*dis_car_inter/(drive_lane.straightTimeToChange+10+8);// red light 10S, green light 8S
                max_speed = 3.6*dis_car_inter/(drive_lane.straightTimeToChange+10);
            }
            else
            {
                min_speed = 3.6*dis_car_inter/(drive_lane.straightTimeToChange+8);
                max_speed = 3.6*dis_car_inter/(drive_lane.straightTimeToChange);
            }

            if(min_speed >limit_speed){
                temp_RoadData.advice = 7; // advice : keep the speed
                temp_RoadData.advice_speed = current_speed;
            }
            else if(max_speed>limit_speed){
                temp_RoadData.advice_speed = (min_speed+limit_speed)/2;
                if(temp_RoadData.advice_speed<10)
                {
                    temp_RoadData.advice = 6; // advice : stop
                    temp_RoadData.advice_speed = 0;
                }
                else{
                    if(current_speed>min_speed && current_speed<limit_speed){
                        temp_RoadData.advice = 7; // advice: keep the speed
                        temp_RoadData.advice_speed = current_speed;}
                    else if(current_speed < min_speed){
                        diff_speed = fabs(temp_RoadData.advice -current_speed);
                        if(diff_speed<10)
                            temp_RoadData.advice = 8; // advice : speed up softly
                        else
                            temp_RoadData.advice = 9; // advice : speed up rapidly
                    }
                    else if(current_speed >=limit_speed){
                        diff_speed = fabs(current_speed - temp_RoadData.advice_speed);
                        if(diff_speed<10)
                            temp_RoadData.advice = 10; // advice : slow down softly
                        else
                            temp_RoadData.advice = 11; // advice : slow down rapidly
                    }
                }
            }
            else{
                temp_RoadData.advice_speed = (min_speed+max_speed)/2;
                if( temp_RoadData.advice_speed < 10 && relative_A.y > 0){
                    temp_RoadData.advice = 12; // advice: stop the car
                }
                else if(temp_RoadData.advice_speed < 10 && relative_A.y < 0 &&
                        drive_lane.straightState == YELLOWLIGHT){
                    temp_RoadData.advice = 13;
                }
                else{
                    if(current_speed>min_speed && current_speed<max_speed)
                        temp_RoadData.advice = 13;  // advice : keep the speed
                    else if(current_speed <min_speed){
                        diff_speed = fabs(temp_RoadData.advice_speed - current_speed);
                        if(diff_speed<10)
                            temp_RoadData.advice = 14; // advice : speed up softly
                        else
                            temp_RoadData.advice = 15; // advice : speed up rapidly
                    }
                    else if(current_speed >=max_speed){
                        diff_speed = fabs(current_speed - temp_RoadData.advice_speed);
                        if(diff_speed<10)
                            temp_RoadData.advice = 16; // advice : slow down softly
                        else
                            temp_RoadData.advice = 17; // advice : slow down rapidly
                    }
                }
            }            
        }


        std::cout<<"==Road Data==\n";
        std::cout<<"dis_car_inter:"<<dis_car_inter<<"\n"<<std::endl;
        std::cout<<" light ID    : "<<temp_RoadData.deviceId<<"\n"
                 <<"signal phase : "<<temp_RoadData.signal_phase<<"\n"
                 <<"left time    : "<<temp_RoadData.remain_time<<"\n"
                 <<"Advice       : "<<temp_RoadData.advice<<"\n "
                 <<"Advice speed : "<<temp_RoadData.advice_speed<<"\n";
        std::cout<<"======================================\n";

        Intersections_.clear();
        _lcm.publish(CVM_CHANNEL_HMI_ROAD_PUB, &temp_RoadData);
    }
}


}


}

}
