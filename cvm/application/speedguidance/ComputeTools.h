/**
 * @file computetools.h
 * @brief computing functions
 */

#ifndef _CVM_APPLICATION_SPEEDGUIDANCE_COMPUTETOOLS_H_
#define _CVM_APPLICATION_SPEEDGUIDANCE_COMPUTETOOLS_H_

#include <cvm/application/speedguidance/SpeedGuidanceConfig.h>


#define PI 3.1415926535
#include <math.h>

namespace cvm {

namespace application {

namespace speedguidance {

/**
 * @brief cal_Vector_AB
 * @param lat1, long1  GPS coordinate
 * @param lat2, long2
 * @return   a vector
 */
VectorPP cal_Vector_AB(double lat1,double long1,double lat2,double long2);

/**
 * @brief cal_dis_of_GPS
 * @param lat1, long1  GPS coordinate
 * @param lat2, long2
 * @return  the distance of two point
 */
double cal_dis_of_GPS(double lat1, double long1, double lat2, double long2);

double cal_angle_vec_vec(double x1,double y1,double x2,double y2);

void transformGPStoRS(double lat1,double long1,double lat2,double long2, double heading, VectorPP &PP);


}

}

}


#endif
