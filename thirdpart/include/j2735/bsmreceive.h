#ifndef BSMRECEIVE_H
#define BSMRECEIVE_H

#include "BasicSafetyMessage.h"
#include "math.h"
#include <QDebug>


class BSMReceive
{

public:

    int  carID;
    double  latitude;
    double  longitude;
    double  speed;
    double  heading;
    double  wheelAngle;
    bool    carBrake;

    BSMReceive(BasicSafetyMessage *BSMMessage)
    {
        int  tempcarID = 0;
        int  templatitude = 0;
        int  templongitude = 0;
        qint16  tempspeed = 0;
        qint16  tempheading = 0;
        qint8  tempwheelAngle = 0;

        //id (2 - 5)
        tempcarID = tempcarID | ((int)BSMMessage->blob1.buf[1])<<24;
        tempcarID = tempcarID | ((int)BSMMessage->blob1.buf[2])<<16;
        tempcarID = tempcarID | ((int)BSMMessage->blob1.buf[3])<<8;
        tempcarID = tempcarID | (int)BSMMessage->blob1.buf[4];

        //lat (8 - 11)
        templatitude = templatitude | ((int)BSMMessage->blob1.buf[7])<<24;
        templatitude = templatitude | ((int)BSMMessage->blob1.buf[8])<<16;
        templatitude = templatitude | ((int)BSMMessage->blob1.buf[9])<<8;
        templatitude = templatitude | (int)BSMMessage->blob1.buf[10];


        //long (12 - 15)
        templongitude = templongitude | ((int)BSMMessage->blob1.buf[11])<<24;
        templongitude = templongitude | ((int)BSMMessage->blob1.buf[12])<<16;
        templongitude = templongitude | ((int)BSMMessage->blob1.buf[13])<<8;
        templongitude = templongitude | (int)BSMMessage->blob1.buf[14];


        //speed (22 - 23)
        tempspeed = tempspeed | ((int)BSMMessage->blob1.buf[21] & 0x1F)<<8;
        tempspeed = tempspeed | (int)BSMMessage->blob1.buf[22];


        //Heading (24 - 25)
        tempheading = tempheading | ((int)BSMMessage->blob1.buf[23])<<8;
        tempheading = tempheading | (int)BSMMessage->blob1.buf[24];


        //angle (26)
        tempwheelAngle = tempwheelAngle | (int)BSMMessage->blob1.buf[25];


        //safetyEvent:Brake
        if(*BSMMessage->safetyExt->events == 128)
        {
            carBrake = true;
        }

        qDebug("%d\n%d\n%d\n%d\n%d\n%d\n",tempcarID,templatitude,templongitude,tempspeed,tempheading,tempwheelAngle);

        //dataChange
        carID = tempcarID;
        latitude = templatitude/1000000.0;
        longitude = templongitude/1000000.0;
        speed = tempspeed/50.0*3.6;
        heading = tempheading*0.0125;
        wheelAngle = tempwheelAngle*1.5;

        qDebug("%d\n%f\n%f\n%f\n%f\n%f\n",carID,latitude,longitude,speed,heading,wheelAngle);
    }
    
    
};

#endif // BSMRECEIVE_H
