#include "C-ITS.h"
#include "ANY.h"
#include "C-ITS/MessageFrame.h"   //in order avoid conflict with j2735, "C-ITS" can't be defaulted
#include "C-ITS/BasicSafetyMessage.h"
#include "C-ITS/MapData.h"
#include "C-ITS/SPAT.h"
#include <iostream>

namespace cvm
{

namespace sensor
{

namespace dsrc
{

int frame_bsm_encode(const char* p_frame_bsm_message, char* p_frame_bsm_buffer, const int p_frame_bsm_message_length)
{
    asn_enc_rval_t er;
    MessageFrame_t *p_frame_bsm = NULL;
    int encode_size = -1;

    /*Init.*/
    p_frame_bsm = (MessageFrame_t*)calloc(sizeof(MessageFrame_t), 1);
    p_frame_bsm->messageId = 20;

    do {
        /*Parameter judgement.*/
        if (NULL == p_frame_bsm_message ) {
            printf("pointer parameter error.\n");
            break;
        }
        if (p_frame_bsm_message_length <= 0) {
            printf("length parameter error.\n");
            break;
        }

        /*Fill 'p_frame_bsm' by 'p_frame_bsm_message'.*/
         OCTET_STRING_fromBuf(reinterpret_cast<OCTET_STRING_t*>(&(p_frame_bsm->value)), p_frame_bsm_message, p_frame_bsm_message_length);
        p_frame_bsm->value.buf = (uint8_t*)calloc(p_frame_bsm_message_length, 1);
        memcpy(p_frame_bsm->value.buf, p_frame_bsm_message, p_frame_bsm_message_length);
        p_frame_bsm->value.size = p_frame_bsm_message_length;
        /*Encode 'p_frame_bsm' into 'p_frame_bsm_buffer'.*/
        er = der_encode_to_buffer(&asn_DEF_MessageFrame, p_frame_bsm, p_frame_bsm_buffer, 1024);

        std::cout<<"frame_bsm_encode_length = "<<er.encoded<<std::endl;
        encode_size = er.encoded;
    } while (0);

    asn_DEF_MessageFrame.free_struct(&asn_DEF_MessageFrame, p_frame_bsm, 0);
    return encode_size;
}

int frame_bsm_decode(char* p_frame_bsm_message, const char* p_frame_bsm_buffer, const int length)
{
    asn_dec_rval_t rval;
    MessageFrame_t *p_frame_bsm = NULL;
    int bsm_size = -1;

    /*Init.*/
    p_frame_bsm = (MessageFrame_t*)calloc(sizeof(MessageFrame_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == p_frame_bsm_buffer) {
            printf("pointer parameter error.\n");
            break;
        }
        if (length <= 0) {
            printf("length parameter error.\n");
            break;
        }

        /*Decode 'p_frame_bsm_buffer' into 'p_frame_bsm'.*/
        rval = asn_DEF_MessageFrame.ber_decoder(0, &asn_DEF_MessageFrame, (void **)&p_frame_bsm, p_frame_bsm_buffer, length, 0);

        /*If decode error, break.*/
        if (0 != rval.code) {
            printf("frame_bsm_decode fail.\n");
            break;
        }

        /*Fill 'p_frame_bsm_message' by 'p_frame_bsm'.*/
        if (20 == p_frame_bsm->messageId ){
            memcpy(p_frame_bsm_message, p_frame_bsm->value.buf, p_frame_bsm->value.size);
            bsm_size = p_frame_bsm->value.size;
        }

        std::cout<<"frame_bsm_decode_length = "<<rval.consumed<<std::endl;
    } while (0);

    asn_DEF_MessageFrame.free_struct(&asn_DEF_MessageFrame, p_frame_bsm, 0);
    return bsm_size;
}

int bsmDataEncode_CITS(const cvm::protocol::BsmData& bsmData, char *p_bsm_buffer)
{
    asn_enc_rval_t er;
    BasicSafetyMessage_t *p_bsm = NULL;
    int i = 0;
    int encode_size = -1;

    /*Init.*/
    p_bsm = (BasicSafetyMessage_t*)calloc(sizeof(BasicSafetyMessage_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == &bsmData) {
            printf("pointer parameter error.\n");
            break;
        }

        /*Fill 'p_bsm' by 'bsmData'.*/
        p_bsm->msgCnt = 0;

        p_bsm->id.buf = (uint8_t*)calloc(4, 1);
        memcpy(p_bsm->id.buf, &bsmData.carId, 4);
        p_bsm->id.size = 4;

        p_bsm->secMark = 0;
        p_bsm->lat =bsmData.location.latitude;
        p_bsm->Long = bsmData.location.longitude;
        p_bsm->elev = 0;

        OCTET_STRING_fromBuf(reinterpret_cast<OCTET_STRING_t*>(&(p_bsm->accuracy.pos)), "0", 1);
        OCTET_STRING_fromBuf(reinterpret_cast<OCTET_STRING_t*>(&(p_bsm->accuracy.elevation)), "0", 1);
        OCTET_STRING_fromBuf(reinterpret_cast<OCTET_STRING_t*>(&(p_bsm->transmission)), "0", 1);

        p_bsm->speed = bsmData.speed;
        p_bsm->heading = bsmData.azimuth;

        p_bsm->angle = bsmData.steeringWheelAngle;
        p_bsm->accelSet.lat = 0;
        p_bsm->accelSet.Long = 0;
        p_bsm->accelSet.vert = 0;
        p_bsm->accelSet.yaw = 0;
        p_bsm->size.width = 0;
        p_bsm->size.length = 0;
        p_bsm->vehicleClass.classification = 0;
        /*Encode 'p_bsm' into 'p_bsm_buffer'.*/
        er = der_encode_to_buffer(&asn_DEF_BasicSafetyMessage, p_bsm, p_bsm_buffer, 1024);

        std::cout<<"bsm_encode_length = "<<er.encoded<<std::endl;
        encode_size = er.encoded;
    } while (0);

    asn_DEF_BasicSafetyMessage.free_struct(&asn_DEF_BasicSafetyMessage, p_bsm, 0);
    return encode_size;
}

int bsmDataDecode_CITS(cvm::protocol::BsmData& bsmData, const char *p_bsm_buffer, const int length)
{
    asn_dec_rval_t rval;
    BasicSafetyMessage_t *p_bsm = NULL;
    int i = 0;
    int decode_size = -1;

    /*Init.*/
    p_bsm = (BasicSafetyMessage_t*)calloc(sizeof(BasicSafetyMessage_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == p_bsm_buffer) {
            printf("pointer parameter error.\n");
            break;
        }
        if (length <= 0) {
            printf("length parameter error.\n");
            break;
        }

        /*Decode 'p_bsm_buffer' into 'p_bsm'.*/
        rval = asn_DEF_BasicSafetyMessage.ber_decoder(0, &asn_DEF_BasicSafetyMessage, (void **)&p_bsm, p_bsm_buffer, length, 0);

        /*If decode error, break.*/
        if (0 != rval.code) {
            printf("bsm_decode fail.\n");
            break;
        }

        /*Fill 'p_bsm_message' by 'p_bsm'.*/
        //p_bsm_message->msgCnt = p_bsm->msgCnt;
        memcpy(&bsmData.carId, p_bsm->id.buf, p_bsm->id.size);
        //p_bsm_message->secMark = p_bsm->secMark;
        bsmData.location.latitude = p_bsm->lat;
        bsmData.location.longitude = p_bsm->Long;
        //p_bsm_message->elev =p_bsm->elev;
        //p_bsm_message->accuracy = p_bsm->accuracy.pos.buf[0];
        //p_bsm_message->transmission = p_bsm->transmission.buf[0];
        bsmData.speed = p_bsm->speed;
        bsmData.azimuth = p_bsm->heading;
        bsmData.steeringWheelAngle = p_bsm->angle;
        //p_bsm_message->accelLatSet = p_bsm->accelSet.lat;
        //p_bsm_message->accelLong = p_bsm->accelSet.longitude;
        //p_bsm_message->accelVert = p_bsm->accelSet.vert;
        //p_bsm_message->accelYaw = p_bsm->accelSet.yaw;
        //p_bsm_message->vehWidth_MSB = p_bsm->size.width;
        //p_bsm_message->vehLength_WidthLSB = p_bsm->size.vehicleLength;
        //p_bsm_message->vehicleClass = p_bsm->vehicleClass.classification;
        //p_bsm_message->brakeSts = p_bsm->brakes.brakePadel->buf[0];

        std::cout<<"bsm_decode_length = "<<rval.consumed<<std::endl;
        decode_size = rval.consumed;
    } while (0);

    asn_DEF_BasicSafetyMessage.free_struct(&asn_DEF_BasicSafetyMessage, p_bsm, 0);
    return decode_size;
}

int frame_map_decode(char* p_frame_map_message, const char* p_frame_map_buffer, const int length)
{
    asn_dec_rval_t rval;
    MessageFrame_t *p_frame_map = NULL;
    int map_size = -1;

    /*Init.*/
    p_frame_map = (MessageFrame_t*)calloc(sizeof(MessageFrame_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == p_frame_map_buffer) {
            printf("pointer parameter error.\n");
            break;
        }
        if (length <= 0) {
            printf("length parameter error.\n");
            break;
        }

        /*Decode 'p_frame_map_buffer' into 'p_frame_map'.*/
        rval = asn_DEF_MessageFrame.ber_decoder(0, &asn_DEF_MessageFrame, (void **)&p_frame_map, p_frame_map_buffer, length, 0);

        /*If decode error, return -1.*/
        if (0 != rval.code != 0) {
            std::cout<<"frame_map_decode fail."<<std::endl;
            break;
        }

        /*Fill 'p_frame_map_message' by 'p_frame_map'.*/
        if (18 == p_frame_map->messageId) {
            memcpy(p_frame_map_message, p_frame_map->value.buf, p_frame_map->value.size);
            map_size = p_frame_map->value.size;
        }

        std::cout<<"frame_map_decode_length = "<<rval.consumed<<std::endl;
    } while (0);

    asn_DEF_MessageFrame.free_struct(&asn_DEF_MessageFrame, p_frame_map, 0);
    return map_size;
}

int map_decode(cvm::protocol::MapData *p_map_message, const char *p_map_buffer, const int length)
{
    asn_dec_rval_t rval;
    MapData_t *p_map = NULL;
    int i, j = 0;
    int decode_size = -1;

    /*Init.*/
    p_map = (MapData_t*)calloc(sizeof(MapData_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == p_map_buffer) {
            std::cout<<"pointer parameter error."<<std::endl;
            break;
        }
        if (length <= 0) {
            std::cout<<"length parameter error."<<std::endl;
            break;
        }

        /*Decode 'p_map_buffer' into 'p_map'.*/
        rval = asn_DEF_MapData.ber_decoder(0, &asn_DEF_MapData, (void **)&p_map, p_map_buffer, length, 0);

        /*If decode error, break.*/
        if (0 != rval.code) {
            std::cout<<"map_decode fail."<<std::endl;
            break;
        }

        /*Fill 'p_map_message' by 'p_map'.*/
        for (i = 0; i < p_map->nodes.list.count; i++) {
            p_map_message->intersectionId = p_map->nodes.list.array[i]->id.id;
            p_map_message->refPoint.latitude = p_map->nodes.list.array[i]->refPos.lat;
            p_map_message->refPoint.longitude = p_map->nodes.list.array[i]->refPos.Long;
            p_map_message->refPoint.altitude = 0;//目前无值
            p_map_message->approachCount = p_map->nodes.list.array[i]->inLinks->list.count;
            for (j = 0; j < p_map->nodes.list.array[i]->inLinks->list.count; j++) {//还没有得到approach 的 id
                //p_map_message->lane[j].laneNumber = p_map->nodes.list.array[i]->inLinks->list.array[j]->upstreamNodeId.id;
                p_map_message->approach[j].refPoint.latitude = p_map->nodes.list.array[i]->inLinks->list.array[j]->entryLine->offsetLL.choice.position_LatLon.lat;
                p_map_message->approach[j].refPoint.longitude = p_map->nodes.list.array[i]->inLinks->list.array[j]->entryLine->offsetLL.choice.position_LatLon.lon;
                p_map_message->approach[j].refPoint.altitude = 0;//目前无值
                p_map_message->approach[j].approachWidth = 3.5;   //目前无值,给默认值3.5
            }
        }

        std::cout<<"map_decode_length = "<<rval.consumed<<std::endl;
        decode_size = rval.consumed;
    } while (0);

    asn_DEF_MapData.free_struct(&asn_DEF_MapData, p_map, 0);
    return decode_size;
}

int frame_spat_decode(char* p_frame_spat_message, const char* p_frame_spat_buffer, const int length)
{
    asn_dec_rval_t rval;
    MessageFrame_t *p_frame_spat = NULL;
    int spat_size = -1;

    /*Init.*/
    p_frame_spat = (MessageFrame_t*)calloc(sizeof(MessageFrame_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == p_frame_spat_buffer) {
            std::cout<<"pointer parameter error."<<std::endl;
            break;
        }
        if (length <= 0) {
            std::cout<<"length parameter error."<<std::endl;
            break;
        }

        /*Decode 'p_frame_spat_buffer' into 'p_frame_spat'.*/
        rval = asn_DEF_MessageFrame.ber_decoder(0, &asn_DEF_MessageFrame, (void **)&p_frame_spat, p_frame_spat_buffer, length, 0);

        /*If decode error, break.*/
        if (0 != rval.code) {
            std::cout<<"frame_spat_decode fail."<<std::endl;
            break;
        }

        /*Fill 'p_frame_spat_message' by 'p_frame_spat'.*/
        if (19 == p_frame_spat->messageId) {
            memcpy(p_frame_spat_message, p_frame_spat->value.buf, p_frame_spat->value.size);
            spat_size = p_frame_spat->value.size;
        }

        std::cout<<"frame_spat_decode_length = "<<rval.consumed<<std::endl;
    } while (0);

    asn_DEF_MessageFrame.free_struct(&asn_DEF_MessageFrame, p_frame_spat, 0);
    return spat_size;
}

int spat_decode(cvm::protocol::SpatData *p_spat_message, const char *p_spat_buffer, const int length)
{
    asn_dec_rval_t rval;
    SPAT_t *p_spat = NULL;
    int i, j, n, l = 0;
    int decode_size = -1;

    /*Init.*/
    p_spat = (SPAT_t *)calloc(sizeof(SPAT_t), 1);

    do {
        /*Parameter judgement.*/
        if (NULL == p_spat_buffer) {
            std::cout<<"pointer parameter error."<<std::endl;
            break;
        }
        if (length <= 0) {
            std::cout<<"length parameter error."<<std::endl;
            break;
        }

        /*Decode 'p_spat_buffer' into 'p_spat'.*/
        rval = asn_DEF_SPAT.ber_decoder(0, &asn_DEF_SPAT, (void **)&p_spat, p_spat_buffer, length, 0);

        /*If decode error, break.*/
        if (rval.code != 0) {
            std::cout<<"spat_decode fail."<<std::endl;
            break;
        }
        std::cout<<"spat_decode_length = "<<rval.consumed<<std::endl;

        /*Fill 'p_spat_message' by 'p_spat'.*/
//        for (n=0; n<p_spat->intersections.list.count; n++) {
        for (n=0; n < 1; n++) {//简化处理,认为一个spat消息只发送一个路口的信息,实际上有可能发送多个路口的消息
            /*Filter invalid message.*/
            if (p_spat->intersections.list.array[n]->intersectionId.id <= 0) {
                std::cout<<"spat message invalid."<<std::endl;
                continue;
            }

            p_spat_message->intersectionId = (int32_t)(p_spat->intersections.list.array[n]->intersectionId.id);
            //printf("intersectionId(%d) navigationId(%d)\n", p_spat->intersections.list.array[n]->intersectionId.id, p_spat_message->intersectionId);
            for (i=0; i<p_spat->intersections.list.array[n]->phases.list.count; i++) {
                for (j = 0; j < p_spat->intersections.list.array[n]->phases.list.array[i]->phaseStates.list.count; j++) {
//                    p_spat_message[n].lane[i].light[j].lightMode = LIGHTMODE_BALL;
//                    p_spat_message[n].lane[i].light[j].lightState = signal_change_v2x(p_spat->intersections.list.array[n]->phases.list.array[i]->phaseStates.list.array[j]->light.buf[0]);
//                    p_spat_message[n].lane[i].light[j].timeToChange = p_spat->intersections.list.array[n]->phases.list.array[i]->phaseStates.list.array[j]->timing->minEndTime[0];
//                    printf("lightState(%d) timeToChange(%hd) ", p_spat_message[n].lane[i].light[j].lightState, p_spat_message[n].lane[i].light[j].timeToChange);
//                }
//                p_spat_message[n].lane[i].lightLen = p_spat->intersections.list.array[n]->phases.list.array[i]->phaseStates.list.count;
//                printf("lightLen(%hhd)\n", p_spat_message[n].lane[i].lightLen);
//            }

//            p_spat_message[n].lightUpdate =1;
//            p_spat_message[n].lastUpdateTime = 10;

            /*fill map.*/

            }
            ///printf("centerLat(%lf) centerLon(%lf)\n", p_spat_message[n].center.lat, p_spat_message[n].center.lon);
        }
      }

        decode_size = rval.consumed;
    } while (0);

    asn_DEF_SPAT.free_struct(&asn_DEF_SPAT, p_spat, 0);
    return decode_size;
}


}

}

}
