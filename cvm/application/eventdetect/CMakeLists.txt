set(SRCS
  Main.cpp
  EventDetect.cpp
  EventDetectConfig.cpp
  ComputeTools.cpp
  )

add_executable(cvm-app-eventd ${SRCS})
target_link_libraries(cvm-app-eventd lcm glib-2.0 pcre pthread cvm config++)
