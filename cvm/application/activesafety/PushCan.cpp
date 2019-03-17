
#include <assert.h>
#include <time.h>
#include <arpa/inet.h>
#include <cvm/base/Logging.h>
#include <cvm/application/activesafety/CollisionDetec.h>
#include <cvm/protocol/CanCtrlData.hpp>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/base/Timestamp.h>

namespace cvm {

namespace application {

namespace activesafety {

unsigned char tFlow_ = 0;

void VehiclesModel::sendToCanBus()
{
    if(host_vehicle_.get() == NULL
            || vehicles_.size() == 0)
    {
        LDEBUG << "don't send to can.";
        return;
    }

    LDEBUG << "send to can.";

    tFlow_ ++;

    /// self id & speed
    cvm::protocol::CanCtrlData frame_1;
    frame_1.id = 0x600;
    frame_1.length = 7;
    frame_1.data[0] = tFlow_;
    *(int*)(frame_1.data+1) = htonl(host_vehicle_->id);
    *(short*)(frame_1.data+5) = htons((short)host_vehicle_->speed * 50);
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_1);

    /// self longitude
    cvm::protocol::CanCtrlData frame_2;
    frame_2.id = 0x601;
    frame_2.length = 7;
    frame_2.data[0] = tFlow_;
    *(short*)(frame_2.data+1) = htons((short)host_vehicle_->longitude*10000000000/4294967296);
    *(int*)(frame_2.data+1) = htonl((int)host_vehicle_->longitude*10000000000%4294967296);
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_2);

    /// self latitude
    cvm::protocol::CanCtrlData frame_3;
    frame_3.id = 0x602;
    frame_3.length = 7;
    frame_3.data[0] = tFlow_;
    *(short*)(frame_3.data+1) = htons((short)host_vehicle_->latitude*10000000000/4294967296);
    *(int*)(frame_3.data+1) = htonl((int)host_vehicle_->latitude*10000000000%4294967296);
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_3);

    /// self elevation & heading
    cvm::protocol::CanCtrlData frame_4;
    frame_4.id = 0x603;
    frame_4.length = 7;
    frame_4.data[0] = tFlow_;
    *(int*)(frame_4.data+1) = htonl((int)host_vehicle_->altitude*10);
    *(short*)(frame_4.data+5) = htons((short)host_vehicle_->heading/0.0125);
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_4);

    /// self vehicle size & warnings
    cvm::protocol::CanCtrlData frame_5;
    frame_5.id = 0x604;
    frame_5.length = 7;
    frame_5.data[0] = tFlow_;
    frame_5.data[1] = 1.5*10;
    frame_5.data[2] = 1.5*10;
    frame_5.data[3] = 1.5*10;
    if(detect_results_.size() > 0)
    {
        frame_5.data[4] = (char)detect_results_.begin()->second.wStr;
        frame_5.data[5] = (char)detect_results_.begin()->second.wPrio;
        frame_5.data[6] = (char)detect_results_.begin()->second.wLvl;
    }
    else
    {
        frame_5.data[4] = (char)0;
        frame_5.data[5] = (char)0;
        frame_5.data[6] = (char)0;
    }
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_5);

    /// Time: hour minute second
    cvm::protocol::CanCtrlData frame_6;
    frame_6.id = 0x605;
    frame_6.length = 7;
    frame_6.data[0] = tFlow_;
    time_t t = cvm::base::Timestamp::now().secondsSinceEpoch();
    tm *p = gmtime(&t);
    *(short*)(frame_6.data+1) = htons((short)p->tm_hour);
    *(short*)(frame_6.data+3) = htons((short)p->tm_min);
    *(short*)(frame_6.data+5) = htons((short)p->tm_sec * 1000);
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_6);

    /// TTC THW
    cvm::protocol::CanCtrlData frame_7;
    frame_7.id = 0x606;
    frame_7.length = 7;
    frame_7.data[0] = tFlow_;
    if(detect_results_.size() > 0)
    {
        *(short*)(frame_7.data+1) = htons((short)(detect_results_.begin()->second.TTC * 10));
        *(short*)(frame_7.data+1) = htons((short)(detect_results_.begin()->second.THW * 10));
        *(short*)(frame_7.data+1) = htons((short)detect_results_.begin()->second.trend);
    }
    else
    {
        *(short*)(frame_7.data+1) = htons((short)0);
        *(short*)(frame_7.data+1) = htons((short)0);
        *(short*)(frame_7.data+1) = htons((short)0);
    }
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_7);

    /// prePath[0]
    cvm::protocol::CanCtrlData frame_8;
    frame_8.id = 0x607;
    frame_8.length = 7;
    frame_8.data[0] = tFlow_;
    if(host_vehicle_->prePath.size() > 2)
    {
        *(short*)(frame_8.data+1) = htons((short)(host_vehicle_->prePath[0].x_ * 10));
        *(short*)(frame_8.data+1) = htons((short)(host_vehicle_->prePath[0].y_ * 10));
    }
    else
    {
        *(short*)(frame_8.data+1) = htons((short)(0));
        *(short*)(frame_8.data+1) = htons((short)(0));
    }
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_8);

    /// prePath[1]
    cvm::protocol::CanCtrlData frame_9;
    frame_9.id = 0x608;
    frame_9.length = 7;
    frame_9.data[0] = tFlow_;
    if(host_vehicle_->prePath.size() > 2)
    {
        *(short*)(frame_9.data+1) = htons((short)(host_vehicle_->prePath[1].x_ * 10));
        *(short*)(frame_9.data+1) = htons((short)(host_vehicle_->prePath[1].y_ * 10));
    }
    else
    {
        *(short*)(frame_9.data+1) = htons((short)(0));
        *(short*)(frame_9.data+1) = htons((short)(0));
    }
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_9);

    /// prePath[2]
    cvm::protocol::CanCtrlData frame_10;
    frame_10.id = 0x609;
    frame_10.length = 7;
    frame_10.data[0] = tFlow_;
    if(host_vehicle_->prePath.size() > 2)
    {
        *(short*)(frame_10.data+1) = htons((short)(host_vehicle_->prePath[2].x_ * 10));
        *(short*)(frame_10.data+1) = htons((short)(host_vehicle_->prePath[2].y_ * 10));
    }
    else
    {
        *(short*)(frame_10.data+1) = htons((short)(0));
        *(short*)(frame_10.data+1) = htons((short)(0));
    }
    lcm_.publish(CVM_CHANNEL_CAN_CTRL, &frame_10);
}

}

}

}
