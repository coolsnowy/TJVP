set(SRCS
  Main.cpp
  SpeedGuidance.cpp
  SpeedGuidanceConfig.cpp
  ComputeTools.cpp
  )

add_executable(cvm-app-speedg ${SRCS})
target_link_libraries(cvm-app-speedg lcm glib-2.0 pcre pthread cvm)
