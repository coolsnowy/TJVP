#include <iostream>
#include <cvm/worldmodel/Intersection.h>
using std::cout;
using std::endl;
namespace cvm
{

namespace worldmodel
{

Intersection::Intersection(int32_t intersectionId)
{
    _intersectionData.intersectionId = intersectionId;
    _tempMapData.approachCount = 0;
}

void Intersection::updateFromMap(const protocol::MapData* msg)
{
    readMapMsg = true;
    _tempMapData.approach.clear();
    _tempMapData.approachCount = 0;
    _tempMapData.intersectionId = msg->intersectionId;
    _tempMapData.approachCount = msg->approachCount;
    _tempMapData.refPoint.longitude = msg->refPoint.longitude;
    _tempMapData.refPoint.latitude = msg->refPoint.latitude;
    _tempMapData.refPoint.altitude = msg->refPoint.altitude;
    protocol::Approach tempApproach;
    for(int i = 0;i < msg->approach.size();i++){
        tempApproach.approachId = msg->approach[i].approachId;
        tempApproach.approachWidth = msg->approach[i].approachWidth;
        tempApproach.refPoint.longitude = msg->approach[i].refPoint.longitude;
        tempApproach.refPoint.latitude = msg->approach[i].refPoint.latitude;
        tempApproach.refPoint.altitude = msg->approach[i].refPoint.altitude;
        _tempMapData.approach.push_back(tempApproach);
    }
    readMapMsg = false;
//    std::cout<<_tempMapData.intersectionId<<std::endl;
//    std::cout<<_tempMapData.approachCount<<std::endl;
//    std::cout<<_tempMapData.refPoint.longitude<<std::endl;
//    std::cout<<_tempMapData.refPoint.latitude<<std::endl;
//    std::cout<<_tempMapData.refPoint.altitude<<std::endl;
//    std::cout<<std::endl;
//    for(int j = 0;j < _tempMapData.approach.size();j++){
//        std::cout<<_tempMapData.approach[j].approachId<<std::endl;
//        std::cout<<_tempMapData.approach[j].approachWidth<<std::endl;
//        std::cout<<_tempMapData.approach[j].refPoint.longitude<<std::endl;
//        std::cout<<_tempMapData.approach[j].refPoint.latitude<<std::endl;
//        std::cout<<_tempMapData.approach[j].refPoint.altitude<<std::endl;
//        std::cout<<std::endl;
//    }
}

void Intersection::updateFromSpat(const protocol::SpatData *msg)
{
    while(readMapMsg)
        ;

        _intersectionData.lanes.clear();
        _intersectionData.approachCount = _tempMapData.approachCount;
        _intersectionData.refPoint.longitude = _tempMapData.refPoint.longitude;
        _intersectionData.refPoint.latitude = _tempMapData.refPoint.latitude;
        _intersectionData.refPoint.altitude = _tempMapData.refPoint.altitude;

        for(int i = 0;i < msg->light.size();i++){
            protocol::Lane lane;
            lane.approachId = msg->light[i].approachId;
            lane.rightTimeToChange = msg->light[i].rightTimeToChange;
            lane.leftTimeToChange = msg->light[i].leftTimeToChange;
            lane.straightTimeToChange = msg->light[i].straightTimeToChange;
            lane.rightState = msg->light[i].rightState;
            lane.leftState = msg->light[i].leftState;
            lane.straightState = msg->light[i].straightState;
            for (int k = 0;k < 3;k++){
                lane.rightTime[k] = msg->light[i].rightTime[k];
                lane.leftTime[k] = msg->light[i].leftTime[k];
                lane.straightTime[k] = msg->light[i].straightTime[k];
            }
            int j = 0;
            for(;j < _tempMapData.approach.size();j++){
                if(lane.approachId == _tempMapData.approach[j].approachId){
                    lane.approachWidth = _tempMapData.approach[j].approachWidth;
                    lane.refPoint.longitude = _tempMapData.approach[j].refPoint.longitude;
                    lane.refPoint.latitude = _tempMapData.approach[j].refPoint.latitude;
                    lane.refPoint.altitude = _tempMapData.approach[j].refPoint.altitude;
                    break;
                }
                if(j == _tempMapData.approach.size()){
                    std::cout<<"spat 匹配 map 时未正常匹配,lane id is :"<<lane.approachId<<std::endl;
                    lane.approachWidth = 0;
                    lane.refPoint.longitude = 0;
                    lane.refPoint.latitude = 0;
                    lane.refPoint.altitude = 0;
                }
            }
            _intersectionData.lanes.push_back(lane);
        }
        cout<<"********************************************************"<<endl;
        cout<<"##intersec id:  "<<_intersectionData.intersectionId<<endl;
        cout<<"##approach count  :"<<_intersectionData.approachCount<<endl;
        cout<<"##intersec refPoint long:  "<<_intersectionData.refPoint.longitude<<endl;
        cout<<"##intersec refPoint lat:  "<<_intersectionData.refPoint.latitude<<endl;
        cout<<"##intersec refPoint altit:  "<<_intersectionData.refPoint.altitude<<endl;
        cout<<endl;
        for(int k = 0;k <_intersectionData.lanes.size();k++){
            cout<<"###################################"<<endl;
            cout<<"##approach id:  "<<_intersectionData.lanes[k].approachId<<endl;
            cout<<"##approach width:  "<<_intersectionData.lanes[k].approachWidth<<endl;
            cout<<"##approach refPoint long:  "<<_intersectionData.lanes[k].refPoint.longitude<<endl;
            cout<<"##approach refPoint lat:  "<<_intersectionData.lanes[k].refPoint.latitude<<endl;
            cout<<"##approach refPoint altit:  "<<_intersectionData.lanes[k].refPoint.altitude<<endl;
            cout<<"##approach RtimeChange:  "<<_intersectionData.lanes[k].rightTimeToChange<<endl;
            cout<<"##approach StimeChange :  "<<_intersectionData.lanes[k].straightTimeToChange<<endl;
            cout<<"##approach LtimeChange:  "<<_intersectionData.lanes[k].leftTimeToChange<<endl;
            cout<<"##approach Rstate:  "<<_intersectionData.lanes[k].rightState<<endl;
            cout<<"##approach Sstate:  "<<_intersectionData.lanes[k].straightState<<endl;
            cout<<"##approach Lstate:  "<<_intersectionData.lanes[k].leftState<<endl;
            cout<<"##approach RtimeR:  "<<_intersectionData.lanes[k].rightTime[0]<<endl;
            cout<<"##approach RtimeY:  "<<_intersectionData.lanes[k].rightTime[1]<<endl;
            cout<<"##approach RtimeG:  "<<_intersectionData.lanes[k].rightTime[2]<<endl;
            cout<<"##approach StimeR:  "<<_intersectionData.lanes[k].straightTime[0]<<endl;
            cout<<"##approach StimeY:  "<<_intersectionData.lanes[k].straightTime[1]<<endl;
            cout<<"##approach StimeG:  "<<_intersectionData.lanes[k].straightTime[2]<<endl;
            cout<<"##approach LtimeR:  "<<_intersectionData.lanes[k].leftTime[0]<<endl;
            cout<<"##approach LtimeY:  "<<_intersectionData.lanes[k].leftTime[1]<<endl;
            cout<<"##approach LtimeG:  "<<_intersectionData.lanes[k].leftTime[2]<<endl;
            cout<<endl;
        }
        cout<<endl;
}

Intersection::~Intersection()
{

}

}

}
