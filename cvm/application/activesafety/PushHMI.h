/**
  * @file pushhmi.h
  * @brief 定义了PushHmi类
  */

#ifndef PUSHHMI_H
#define PUSHHMI_H

#include <string>
#include <memory>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cjson/cJSON.h>

#include <cvm/base/NonCopyable.h>
#include <cvm/application/activesafety/CollisionDetec.h>

namespace cvm
{

namespace application
{

namespace activesafety
{

typedef std::shared_ptr<VehiclesModel> VehiclesModelPtr;

/**
 * @class PushHmi类
 * @brief 该类负责按照HMI通信协议对数据进行封装，并使用UDP发送到HMI
 */
class PushHmi : public base::NonCopyable
{
public:
    PushHmi();
    explicit PushHmi(VehiclesModelPtr vsModel);
    ~PushHmi();

    /**
     * @brief 发送封装后的数据到HMI
     */
    void sendUdpToHMI();

private:
    VehiclesModelPtr vsmodel_ptr_;

    int hmi_sockfd_;
    std::string hmi_ip_;
    int hmi_port_;
    sockaddr_in hmi_sockaddr_;

    int debug_sockfd_;
    std::string debug_ip_;
    int debug_port_;
    sockaddr_in debug_sockaddr_;

    /**
     * @brief 封装车辆数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateVehicle_Data();
    /**
     * @brief 封装路侧数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateRoad_Data();
    /**
     * @brief 封装事件数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateEvent_Data();
    /**
     * @brief 封装预警数据
     * @return 封装后的JSON数据包
     */
    cJSON *updateWarning_Data();
};

}

}

}

#endif // PUSHHMI_H

