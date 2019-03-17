/**
  * @file computetools.h
  * @brief 计算工具函数集合
  */
#ifndef COMPUTETOOLS_H
#define COMPUTETOOLS_H

#include <vector>

namespace cvm {

namespace application {

namespace activesafety {


#define PI 3.141592653

struct point{
    double x_;
    double y_;
};

/**
 * @brief 在直角坐标系下，根据线段起点坐标，线段长度，线段角度计算终点坐标
 * @param sPoint 线段起点坐标
 * @param length 线段长度
 * @param angle 线段角度
 * @return 终点坐标
 */
point endPoint(const point &sPoint, const double length, double angle);

/**
 * @brief 根据车辆状态数据、车辆运动模型，计算预测轨迹点坐标集合，并存入参数path中
 * @param sPoint 起点坐标
 * @param heading 相对航向角
 * @param wAngle 方向盘转角
 * @param speed 速度
 * @param vehicleWidth 车辆宽度
 * @param vehicleLength 车辆长度
 * @param vehicleWheelDis 车辆轮间距
 * @param path 存放预测轨迹点的集合
 */
void predictPath(const point &sPoint, const double heading, const double wAngle,
                 const double speed, const double vehicleWidth, const double vehicleLength,
                 const double vehicleWheelDis, std::vector<point> &path);


/**
 * @brief 计算两点之间的距离
 * @param x1 第一个点的x坐标
 * @param y1 第一个点的y坐标
 * @param x2 第二个点的x坐标
 * @param y2 第二个点的y坐标
 * @return 返回两个点间的距离
 */
double disOfPoints(const double x1, const double y1, const double x2, const double y2);

/**
 * @brief 计算角度1和角度2之间的夹角
 * @param angle1 角度1
 * @param angle2 角度2
 * @return 角度1和角度2的夹角
 */
double DVofAngle(const double angle1, const double angle2);

/**
 * @brief 计算GPS坐标1和GPS坐标2之间的距离
 * @param lon1 GPS坐标1的经度
 * @param lati1 GPS坐标1的纬度
 * @param lon2 GPS坐标2的经度
 * @param lati2 GPS坐标2的纬度
 * @return GPS坐标1和GPS坐标2之间的距离
 */
double disOfGPS(const double lon1, const double lati1, const double lon2, const double lati2);

/**
 * @brief 将GPS中的航向角转换为直角坐标系下的角度
 * @param angle GPS中的航向角
 * @return 直角坐标系下的角度
 */
double gpsAngle_to_coorAngle(double angle);

/**
 * @brief 计算起始点围绕中心点顺时针旋转一定角度的后的坐标点
 * @param rcenter 中心点坐标
 * @param originPoint 起始点坐标
 * @param angle 旋转角度（顺时针）
 * @return 旋转后的坐标点
 */
point pointRotate(const point &rcenter, const point &originPoint, double angle);






//v2p
void transformGPStoRS(double lat1,double long1,double lat2,double long2, double heading,
                      double &x, double &y);
}

}

}

#endif // COMPUTETOOLS_H





