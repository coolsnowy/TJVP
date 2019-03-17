#include <iostream>

#include <j2735/BasicSafetyMessage.h>
#include <j2735/MapData.h>
#include <j2735/ApproachObject.h>
#include <j2735/SPAT.h>
#include <cvm/protocol/Light.hpp>
#include <cvm/base/Logging.h>
#include <cvm/sensor/dsrc/J2735.h>

namespace cvm
{

namespace sensor
{

namespace dsrc
{

std::vector<char> bsmDataEncode(const protocol::BsmData& bsmData)
{
    int32_t carId = bsmData.carId;
    // 7 precision
    int32_t latitude  = static_cast<int32_t>(bsmData.location.latitude * 1000 * 10000);
    int32_t longitude = static_cast<int32_t>(bsmData.location.longitude * 1000 * 10000);
    int16_t speed     = static_cast<int16_t>(bsmData.speed * 50); // 0.02 m/s
    int16_t azimuth   = static_cast<int16_t>(bsmData.azimuth / 0.0125); // 0.0125 degrees
    int32_t steeringWheelAngle = static_cast<int32_t>(bsmData.steeringWheelAngle / 1.5); // 1.5 degrees
    int16_t acceleration = static_cast<int16_t>(bsmData.acceleration * 100);

    char buf[38] = {0};

    // id (1~4)
    *reinterpret_cast<int32_t *>(buf+1) = htonl(carId);

    // lat (7~10)
    // range: -900000000 ~ 900000000, unavailable:900000001
    if(latitude>900000000 || latitude < -900000000) {
        latitude = 900000001;
    }    
    *reinterpret_cast<int32_t *>(buf+7) = htonl(latitude);

    // long (11~14)
    // range: -1800000000 ~ 1800000000, unavailable:1800000001
    if(longitude>1800000000 || longitude<-1800000000) {
        longitude = 1800000001;
    }
    *reinterpret_cast<int32_t *>(buf + 11) = htonl(longitude);

    // speed (21~22)
    // range: 0 ~ 8192
    *reinterpret_cast<int16_t *>(buf + 21) = htons(speed);

    // azimuth (23~24)
    // range:0 ~ 28799, unavailable:28800
    if(azimuth<0 || azimuth>28799) {
        azimuth = 28800;
    }
    *reinterpret_cast<int16_t *>(buf + 23) = htons(azimuth);

    // angle (25)
    buf[25] = steeringWheelAngle;

    // acceleration(26~27)
    if(acceleration<0 || acceleration>5000) {
        acceleration = -1;
    }

    // "Acceleration" field may be different from the standard.
    *reinterpret_cast<int16_t *>(buf + 26) = htons(acceleration);

    struct BasicSafetyMessage *bsm = reinterpret_cast<BasicSafetyMessage *>(::calloc(1, sizeof(struct BasicSafetyMessage)));
    bsm->msgID = DSRCmsgID::DSRCmsgID_basicSafetyMessage;
    ::OCTET_STRING_fromBuf(&bsm->blob1, buf, sizeof(buf));

    // Encode
    char message[1024];
    asn_enc_rval_t er;
    er = ::der_encode_to_buffer(&::asn_DEF_BasicSafetyMessage, bsm, message, sizeof(message));
    ::asn_DEF_BasicSafetyMessage.free_struct(&::asn_DEF_BasicSafetyMessage, bsm, 0);

    if(er.encoded != -1) {
        return std::vector<char>(message, message + er.encoded);
    }else {
        return std::vector<char>();
    }
}

protocol::BsmData bsmDataDecode(const char* data, int64_t size)
{
    struct BasicSafetyMessage *bsm = nullptr;
      asn_dec_rval_t rval;
      rval = ::asn_DEF_BasicSafetyMessage.ber_decoder(0, &::asn_DEF_BasicSafetyMessage,
              reinterpret_cast<void **>(&bsm), data, size, 0);
      protocol::BsmData bsmData;
      bsmData.carId = -1;
      if(rval.code == RC_OK) {
          int32_t carId;
          int32_t latitude;
          int32_t longitude;
          int32_t speed;
          int32_t azimuth;
          int32_t acceleration;
          int8_t  steeringWheelAngle;

          // id (1 - 4)
          carId = ntohl(*reinterpret_cast<int32_t *>(bsm->blob1.buf + 1));

          // lat (7 - 10)
          latitude = ntohl(*reinterpret_cast<int32_t *>(bsm->blob1.buf + 7));

          // long (11 - 14)
          longitude = ntohl(*reinterpret_cast<int32_t *>(bsm->blob1.buf + 11));

          // speed (21 - 22)
          speed = ntohs(*reinterpret_cast<int16_t *>(bsm->blob1.buf + 21));

          // azimuth (23 - 24)
          azimuth = ntohs(*reinterpret_cast<int16_t *>(bsm->blob1.buf + 23));

          // angle (25)
          steeringWheelAngle = bsm->blob1.buf[25];

          // acceleration (26 - 27)
          acceleration = ntohs(*reinterpret_cast<int16_t *>(bsm->blob1.buf + 26));

          bsmData.carId        = carId;
          bsmData.location.latitude     = latitude / (1000 * 10000.0);
          bsmData.location.longitude    = longitude / (1000 * 10000.0);
          bsmData.speed        = speed / 50.0;
          bsmData.azimuth      = azimuth * 0.0125;
          bsmData.steeringWheelAngle = steeringWheelAngle * 1.5;
          bsmData.acceleration = acceleration / 100.0;

          ::asn_DEF_BasicSafetyMessage.free_struct(&::asn_DEF_BasicSafetyMessage, bsm, 0);
      }
          return bsmData;
}

protocol::MapData mapDataDecode(const char* data, int64_t size)
{
    protocol::MapData mapData;
    mapData.intersectionId = -1;

    MapData_t *map = nullptr;
    asn_dec_rval_t rval;
    rval = ::asn_DEF_MapData.ber_decoder(0, &::asn_DEF_MapData,
                                         reinterpret_cast<void**>(&map), data, size, 0);
    if(rval.code != RC_OK) {
        ::asn_DEF_MapData.free_struct(&::asn_DEF_MapData, map, 0);
        return mapData;
    }

    //xer_fprint(stdout, &asn_DEF_MapData, map);

    // Assume one map message only contains one intersection information
    Intersection_t **inters     = map->intersections->list.array;
    Intersection_t  *inter      = nullptr;
    int              intercount = 1; //map->intersections->list.count;

    ApproachObject_t **approaches  = nullptr;
    ApproachObject_t  *approach    = nullptr;
    int                approachcount  = 0;

    for (int i=0; i<intercount; i++) {
        inter = inters[i];
        mapData.intersectionId  = ntohs(*reinterpret_cast<short *>(inter->id.buf));
        approaches = inter->approaches.list.array;
        approachcount = inter->approaches.list.count;
        mapData.refPoint.latitude  = inter->refPoint->lat / (1000 * 10000.0);
        mapData.refPoint.longitude = inter->refPoint->Long / (1000 * 10000.0);
        mapData.refPoint.altitude = 0;

        mapData.approachCount = approachcount;
        mapData.approach.resize(mapData.approachCount);
        for (int j=0; j<approachcount; j++) {
            approach = approaches[j];
            mapData.approach[j].refPoint.latitude  = approach->refPoint->lat / (1000 * 10000.0);
            mapData.approach[j].refPoint.longitude = approach->refPoint->Long / (1000 * 10000.0);
            mapData.approach[j].refPoint.altitude  = 0;
            mapData.approach[j].approachId = *approach->approach->id;//approachWidth has no value!
        }
    }
    ::asn_DEF_MapData.free_struct(&::asn_DEF_MapData, map, 0);

    return mapData;
}


// it's better to rewrite this function, since it's hard to read and understand
protocol::SpatData spatDataDecode(const char* data, int64_t size)
{
    protocol::SpatData spatData;
    spatData.intersectionId = -1;

    SPAT_t* spat = nullptr;

    asn_dec_rval_t rval;
    rval = ::asn_DEF_SPAT.ber_decoder(0, &::asn_DEF_SPAT,
                                      reinterpret_cast<void **>(&spat),
                                      data, size, 0);

    if(rval.code != RC_OK) {
        return spatData;
    }

/* ********f1赛车场那边的解析程序(不知道能否有用),不适用于同济这边*********
    int ttime = 0;
    int lanecount = *spat->intersections.list.array[0]->lanesCnt;
    lanecount = lanecount / 3;
    spatData.intersectionId = ntohs(*reinterpret_cast<short *>(spat->intersections.list.array[0]->id.buf));
    spatData.light.resize(lanecount);

    for(int i=0; i<lanecount; i++) {

        spatData.light[i].approachId = spat->intersections.list.array[0]->states.list.array[i*3]->laneSet.buf[0];
        spatData.light[i].leftState = *spat->intersections.list.array[0]->states.list.array[i*3]->currState/0x10;

        // Left
        spatData.light[i].leftTimeToChange = spat->intersections.list.array[0]->states.list.array[i*3]->timeToChange;
        ttime = *(spat->intersections.list.array[0]->states.list.array[i*3]->pedCount);
        spatData.light[i].leftTime[0]  = ttime / 65536;
        ttime %= 65536;
        spatData.light[i].leftTime[1] = ttime / 256;
        ttime %= 256;
        spatData.light[i].leftTime[2] = ttime;

        // Straight
        spatData.light[i].straightState = *spat->intersections.list.array[0]->states.list.array[i*3+1]->currState/0x1000;
        spatData.light[i].straightTimeToChange = spat->intersections.list.array[0]->states.list.array[i*3+1]->timeToChange;
        ttime = *(spat->intersections.list.array[0]->states.list.array[i*3+1]->pedCount);
        spatData.light[i].straightTime[0] = ttime / 65536;
        ttime = ttime % 65536;
        spatData.light[i].straightTime[1] = ttime / 256;
        ttime %= 256;
        spatData.light[i].straightTime[2] = ttime;

        // Right
        spatData.light[i].rightState = *spat->intersections.list.array[0]->states.list.array[i*3+2]->currState/0x100;
        spatData.light[i].rightTimeToChange = spat->intersections.list.array[0]->states.list.array[i*3+2]->timeToChange;
        ttime = *(spat->intersections.list.array[0]->states.list.array[i*3+2]->pedCount);
        spatData.light[i].rightTime[0] = ttime / 65536;
        ttime = ttime % 65536;
        spatData.light[i].rightTime[1] = ttime / 256;
        ttime %= 256;
        spatData.light[i].rightTime[2] = ttime;
    }

    ::asn_DEF_SPAT.free_struct(&::asn_DEF_SPAT, spat, 0);

    return spatData;
*/

    int ttime = 0;
    int lanecount = 0;
    if(2 == spat->intersections.list.array[0]->id.size){
        spatData.intersectionId = ntohs ((*(short *) spat->intersections.list.array[0]->id.buf));
    }
    else{
        return spatData;
    }

    if((*spat->intersections.list.array[0]->lanesCnt)){
        lanecount = *spat->intersections.list.array[0]->lanesCnt;
        spatData.approachCount = lanecount;
    }
    else{
        lanecount = 4;//not a good idea
        spatData.approachCount = lanecount;
    }

    spatData.light.resize(0);//先讲light的大小定义为0

    int moveMentNumber = spat->intersections.list.array[0]->states.list.count;//一个灯的信息,可能几条车道的灯的状况是相同的,比如东西走向,南北走向

    for(int i=0;i<moveMentNumber;i++)//一个路口可能发送若干灯的信息,movementNumber
    {
        int laneCnt = *spat->intersections.list.array[0]->states.list.array[i]->laneCnt;
        for(int j=0;j<laneCnt;j++)//一个灯的信息可能对应几个车道
        {
            int approachId = spat->intersections.list.array[0]->states.list.array[i]->laneSet.buf[j];//lane id - 1;作为索引
            cvm::protocol::Light tempLight;
            tempLight.approachId = spat->intersections.list.array[0]->states.list.array[i]->laneSet.buf[j];

            if(*spat->intersections.list.array[0]->states.list.array[i]->currState < 0x10){
                //qDebug("qiudeng");
                tempLight.straightState = *spat->intersections.list.array[0]->states.list.array[i]->currState;
                tempLight.leftState = *spat->intersections.list.array[0]->states.list.array[i]->currState;
                tempLight.rightState = 1;//green all the time
                tempLight.straightTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
                tempLight.leftTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
                tempLight.rightTimeToChange = 0;
                ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);//can turn right any time
                tempLight.leftTime[0]=ttime / 65536;
                ttime %= 65536;
                tempLight.leftTime[1]=ttime / 256;
                ttime %= 256;
                tempLight.leftTime[2]=ttime;
                ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
                tempLight.straightTime[0]=ttime / 65536;
                ttime %= 65536;
                tempLight.straightTime[1]=ttime / 256;
                ttime %= 256;
                tempLight.straightTime[2]=ttime;
                tempLight.rightTime[0] = 0;
                tempLight.rightTime[1] = 0;
                tempLight.rightTime[2] = 0;
//                  std::cout<<tempLight.straightTime[0]<<std::endl;
//                  std::cout<<tempLight.straightTime[1]<<std::endl;
//                  std::cout<<tempLight.straightTime[2]<<std::endl;
            }
            else if(*spat->intersections.list.array[0]->states.list.array[i]->currState < 0x100){
//                  std::cout<<("left")<<std::endl;
                tempLight.straightTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
                tempLight.straightState = *spat->intersections.list.array[0]->states.list.array[i]->currState/0x10;
                ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
                tempLight.leftTime[0]  = ttime / 65536;
                ttime %= 65536;
                tempLight.leftTime[1] = ttime / 256;
                ttime %= 256;
                tempLight.leftTime[2] = ttime;

            }
            else if(*spat->intersections.list.array[0]->states.list.array[i]->currState < 0x1000){
//                  std::cout<<("right")<<std::endl;
                tempLight.rightTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
                tempLight.rightState = *spat->intersections.list.array[0]->states.list.array[i]->currState/0x100;
                ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
                tempLight.rightTime[0]  = ttime / 65536;
                ttime %= 65536;
                tempLight.rightTime[1] = ttime / 256;
                ttime %= 256;
                tempLight.rightTime[2] = ttime;
            }
            else if(*spat->intersections.list.array[0]->states.list.array[i]->currState <= 0x4000){
//                  std::cout<<("straight")<<std::endl;
                tempLight.straightTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
                tempLight.straightState = *spat->intersections.list.array[0]->states.list.array[i]->currState/0x1000;

                ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
                tempLight.straightTime[0]  = ttime / 65536;
                ttime %= 65536;
                tempLight.straightTime[1] = ttime / 256;
                ttime %= 256;
                tempLight.straightTime[2] = ttime;
            }
            else{
                std::cout<<"!!!!error on decode spatData!"<<std::endl;
                return spatData;
            }
          spatData.light.push_back(tempLight);
        }
    }
//    std::cout<<"light的大小: "<<spatData.light.size()<<std::endl;
  ::asn_DEF_SPAT.free_struct(&::asn_DEF_SPAT, spat, 0);

  return spatData;
}

}

}

}
