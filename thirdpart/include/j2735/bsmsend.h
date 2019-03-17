#ifndef BSMSEND_H
#define BSMSEND_H

#include "BasicSafetyMessage.h"
#include "math.h"
#include <QDebug>

class BSMSend
{
public:   
    BasicSafetyMessage *BSMMessage;

    BSMSend(int carID,double latitude,double longitude,double speed,double heading,double wheelAngle,bool carBrake)
    {
        //ÊýÖµ×ª»»
        int newcarID = carID;
        int newlatitude =  (int)round(latitude*1000000);
        int newlongitude =  (int)round(longitude*1000000);
        int newspeed = (int)round(speed/3.6*50);
        int newheading = (int)round(heading/0.0125);
        int newwheelAngle = (int)round(wheelAngle/1.5);


        //BSMMessage
        BSMMessage = (BasicSafetyMessage*)calloc(1,sizeof(BasicSafetyMessage));
        if(!BSMMessage)
        {
            printf("error BSMMessage calloc");
            return;
        }
        //BSMMessage.msgID
        BSMMessage->msgID = DSRCmsgID_basicSafetyMessage;


        //BSMMessage.blob1
        char *buf = (char*)calloc(38, sizeof(char));


        //id (2 - 5)
        buf[4] = newcarID & 0xFF;
        buf[3] = (newcarID & 0xFF00)>>8;
        buf[2] = (newcarID & 0xFF0000)>>16;
        buf[1] = (newcarID & 0xFF000000)>>24;

        //lat (8 - 11)
        if(newlatitude>900000000 && newlatitude < -900000000) //range: -900000000 ~ 900000000,unavailable:900000001
        {
            newlatitude = 900000001;
        }
        buf[10] = newlatitude & 0xFF;
        buf[9] = (newlatitude & 0xFF00)>>8;
        buf[8] = (newlatitude & 0xFF0000)>>16;
        buf[7] = (newlatitude & 0xFF000000)>>24;

        //long (12 - 15)
        if(newlongitude>1800000000 && newlongitude<-1800000000) //range: -1800000000 ~ 1800000000,unavailable:1800000001
        {
            newlongitude = 1800000001;
        }
        buf[14] = newlongitude & 0xFF;
        buf[13] = (newlongitude & 0xFF00)>>8;
        buf[12] = (newlongitude & 0xFF0000)>>16;
        buf[11] = (newlongitude & 0xFF000000)>>24;

        //speed (22 - 23)                //range: 0 ~ 8192
        buf[22] = newspeed & 0xFF;
        buf[21] = (newspeed & 0x1F00)>>8;

        //Heading (24 - 25)
        if(newheading<0 && newheading>28799) //range:0 ~ 28799,unavailable:28800
        {
            newheading = 28800;
        }
        buf[24] = newheading & 0xFF;
        buf[23] = (newheading & 0xFF00)>>8;

        //angle (26)
        if(newwheelAngle<-126 && newwheelAngle>126) //range: -126 ~ 126,unavailable:127
        {
            newwheelAngle = 127;
        }
        buf[25] = newwheelAngle & 0xFF;

        if(OCTET_STRING_fromBuf(&BSMMessage->blob1, buf, 38) != 0)
        {
            printf("error BSMMessage->blob1 calloc");
            return;
        }

        //BSMMessage.VehicleSafetyExtension.EvenFlags
        if(carBrake)
        {
            BSMMessage->safetyExt = (VehicleSafetyExtension*)calloc(1,sizeof(VehicleSafetyExtension));
            if(!BSMMessage->safetyExt)
            {
                printf("error BSMMessage->safetyExt calloc");
                return;
            }
            BSMMessage->safetyExt->events = (EventFlags_t*)calloc(1,sizeof(EventFlags_t));
            if(!BSMMessage->safetyExt->events)
            {
                printf("error BSMMessage->safetyExt->events calloc");
                return;
            }
            *(BSMMessage->safetyExt->events) = 128;
        }

        //print the BSM struct
        xer_fprint(stdout, &asn_DEF_BasicSafetyMessage, BSMMessage);

    }



};


#endif // BSMSEND_H
