set(SRCS
  Main.cpp
  WorldModel.cpp
  WorldModelConfig.cpp
  Vehicle.cpp
  VehicleQueue.cpp
  Intersection.cpp
  IntersectionQueue.cpp
  )

add_executable(cvm-worldmodel ${SRCS})
target_link_libraries(cvm-worldmodel lcm glib-2.0 pcre pthread cvm config++)

