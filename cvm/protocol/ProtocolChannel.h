/**
 * @file ProtocolChannel.h
 * @brief 定义在LCM中传输数据的Channel
 */
#ifndef _CVM_PROTOCOL_PROTOCOLCHANNEL_H_
#define _CVM_PROTOCOL_PROTOCOLCHANNEL_H_

// Protocol Channel Macro Definition

/** 
 * @brief GPS数据的Channel
 */
#define CVM_CHANNEL_GPS_PUB    "CVM_CHANNEL_GPS_PUB"

/**
 * @brief CAN数据的Channel
 */
#define CVM_CHANNEL_CAN_PUB    "CVM_CHANNEL_CAN_PUB"

/** 
 * @brief CAN控制数据的Channel
 */
#define CVM_CHANNEL_CAN_CTRL   "CVM_CHANNEL_CAN_CTRL"

/**
 * @brief 超声波数据的Channel
 */
#define CVM_CHANNEL_ULTRASONIC_PUB "CVM_CHANNEL_ULTRASOMIC_PUB"

/** 
 * @brief 毫米波雷达数据的Channel
 */
#define CVM_CHANNEL_MILLIMETERWAVE_PUB "CVM_CHANNEL_MILLIMETERWAVE_PUB"

/**
 * @brief BSM数据的Channel
 */
#define CVM_CHANNEL_DSRC_BSM_PUB   "CVM_CHANNEL_DSRC_BSM_PUB"

/** 
 * @brief BSM控制数据的Channel
 */
#define CVM_CHANNEL_DSRC_BSM_CTRL  "CVM_CHANNEL_DSRC_BSM_CTRL"

/**
 * @brief MAP数据的Channel
 */
#define CVM_CHANNEL_DSRC_MAP_PUB   "CVM_CHANNEL_DSRC_MAP_PUB"

/**
 * @brief SPAT数据的Channel
 */
#define CVM_CHANNEL_DSRC_SPAT_PUB  "CVM_CHANNEL_DSRC_SPAT_PUB"

/**
 * @brief 他车数据的Channel
 */
#define CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_PUB  "CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_PUB"

/**
 * @brief 他车控制数据的Channel
 */
#define CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_CTRL "CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_CTRL"

/** 
 * @brief 自车数据的Channel
 */
#define CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB   "CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB"

/**
  * @brief channel of intersection, send to application layer
  */
#define CVM_CHANNEL_WORLDMODEL_INTERSECTION_PUB   "CVM_CHANNEL_WORLDMODEL_INTERSECTION_PUB"

/**
 * created by hsj
 * @brief Vehicle data in HMI
 */
#define CVM_CHANNEL_HMI_VEHICLE_PUB  "CVM_CHANNEL_HMI_VEHICLE_PUB"

/**
 * created by hsj
 * @brief Road data in HMI
 */
#define CVM_CHANNEL_HMI_ROAD_PUB  "CVM_CHANNEL_HMI_ROAD_PUB"

/**
 * created by hsj
 * @brief Event data in HMI
 */
#define CVM_CHANNEL_HMI_EVENT_PUB  "CVM_CHANNEL_HMI_EVENT_PUB"

/**
 * created by hsj
 * @brief Warn data in HMI
 */
#define CVM_CHANNEL_HMI_WARN_PUB  "CVM_CHANNEL_HMI_WARN_PUB"


#endif // _CVM_PROTOCOL_PROTOCOLCHANNEL_H_
