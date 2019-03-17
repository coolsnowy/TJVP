/**
 * @file ActiveSafetyConfig.h
 * @brief ActiveSafety的配置
 */
#ifndef _CVM_APPLICATION_ACTIVESAFETY_ACTIVESAFETYCONFIG_H_
#define _CVM_APPLICATION_ACTIVESAFETY_ACTIVESAFETYCONFIG_H_

#include <string>

#define CVM_APPLICATION_ACTIVESAFETY_CONFIG_FILE "/etc/cvm/cvm-activesafety.conf"

namespace cvm
{

namespace application
{

namespace activesafety
{

/// Parameter for isDangerPossible()
extern const double isDanger_hv_speed_low_;
extern const double isDanger_ov_area_r_high_;

/// Parameter for calVehicleLocation()
extern const double calLoc_hv_wheelangle_high_;
extern const double calLoc_hv_wheelangle_low_;


/// -------------------- split line ------------------------


/// Parameter for is_DNPW_Warning()

/// Parameter for is_ICW_Warning()

/// Parameter for is_INCM_Warning()
extern const double isINCM_ov_area_y_low_;

/// Parameter for is_FCW_Warning()
extern const double isFCW_dis_speed;

/// Parameter for is_PW_Warning()
extern const double isPW_dis_speed;

///Parameter for is_LCW_Warning()
extern const double isLCW_dis_x_min;
extern const double isLCW_dis_x_max;
extern const double isLCW_dis_y_min;
extern const double isLCW_dis_y_max;


/// Collection of the detect result
/// Warning str, priority and level
enum WARN_STR{
    STR_DEFAULT = -1,
    INTERSECT_WARNING_L = 1,
    INTERSECT_WARNING_R = 2,
    DONOTPASS_WARNING = 3,
    PASSINGBY_WARNING_L = 4,
    PASSINGBY_WARNING_R = 5,
    INCOMING_WARNING = 6,
    FCW_WARNING = 7,
    LINECHANGE_WARNING_L = 8,
    LINECHANGE_WARNING_R = 9,

    PEDESTRIANS = 100
};

enum WARN_PRIO{
    PRIO_DEFAULT = -1,
    LOW_PRIO = 0,
    MEDIUM_PRIO = 1,
    HIGH_PRIO = 2
};

enum WARN_LVL{
    LVL_DEFAULT = -1,
    LOW_LVL = 0,
    MEDIUM_LVL = 1,
    HIGH_LVL = 2
};

enum collision_det_Type{
    CIRCLETRACK = 0,
    RECTANGLETRACK=1
};

struct detectResult{
    int id;

    WARN_STR wStr;
    WARN_PRIO wPrio;
    WARN_LVL wLvl;

    bool isIntersect;
    double TTC;
    double THW;
    int trend;
};

/// Define the state of the turn light
enum VEHICLE_TURN_LIGHT{
    TURN_LEFT = -4,
    TURN_NONE = 0,
    TURN_RIGHT = 4
};


/// -------------------- split line ------------------------


/// front_left: REVERSE_DIRECT
extern const double FL_REVERSE_DIR_ov_heading_high_;
extern const double FL_REVERSE_DIR_ov_heading_low_;
extern const double FL_REVERSE_DIR_ov_area_x_low_;

/// front_left: INTERSECT_DIRECT
extern const double FL_INTERSECT_DIR_ov_heading_low_;
extern const double FL_INTERSECT_DIR_ov_heading_high_;

/// front_direct: SAME_DIRECT
extern const double FD_SAME_DIR_ov_heading_low_;
extern const double FD_SAME_DIR_ov_heading_high_;

/// front_direct: REVERSE_DIRECT
extern const double FD_REVERSE_DIR_ov_heading_low_;
extern const double FD_REVERSE_DIR_ov_heading_high_;

/// front_right: INTERSECT_DIRECT
extern const double FR_INTERSECT_DIR_ov_heading_low_;
extern const double FR_INTERSECT_DIR_ov_heading_high_;

/// back_left: SAME_DIRECT
extern const double BL_SAME_DIR_ov_heading_low_;
extern const double BL_SAME_DIR_ov_heading_high_;

/// back_right: SAME_DIRECT
extern const double BR_SAME_DIR_ov_heading_low_;
extern const double BR_SAME_DIR_ov_heading_high_;

/// frequency of sending results to can
/// unit : 100 ms
extern const int NORMAL_FREQUENCY;
extern const int DANGER_FREQUENCY;

/// Time to live : detect results
/// unit : 100 ms
extern const int DETECTRESULTS_TTL;

///
/// Define the OV location area
///
///   ---------------------------
///  |   1    |    2   |    3    |
///  -----------------------------
///  |    4   |    5   |    6    |
///  -----------------------------
///
enum VEHICLE_LOC{
    LOC_DEFAULT = -1,
    FRONT_LEFT_LOC = 1,
    FRONT_DIRECT_LOC = 2,
    FRONT_RIGHT_LOC = 3,
    BACK_LEFT_LOC = 4,
    BACK_DIRECT_LOC = 5,
    BACK_RIGHT_LOC = 6
};


///
/// Define the status of the Vehicle
///
enum VEHICLE_STATUS{
    SAME_DIRECT,
    REVERSE_DIRECT,
    INTERSECT_DIRECT
};

struct ActiveSafetyConfig
{
    ActiveSafetyConfig(int argc, char** argv, const std::string& configFile);

    static void printHelp();
    void printConfig();

    bool debug;
    std::string logPath;
};


}

}

}

#endif // _CVM_APPLICATION_ACTIVESAFETY_ACTIVESAFETYCONFIG_H_
