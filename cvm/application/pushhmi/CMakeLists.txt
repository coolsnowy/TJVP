set(SRCS
  Main.cpp
  PushHMI.cpp
  PushHMIConfig.cpp
  )

add_executable(cvm-app-HMI ${SRCS})
target_link_libraries(cvm-app-HMI lcm glib-2.0 pcre pthread cvm cjson)
