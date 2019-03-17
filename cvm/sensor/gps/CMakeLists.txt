set(SRCS
  Main.cpp
  Gps.cpp
  GpsConfig.cpp
  GpsTransmitterFactory.cpp
  transmitter/NetworkGpsTransmitter.cpp
  )

add_executable(cvm-gps ${SRCS})
target_link_libraries(cvm-gps lcm glib-2.0 pcre pthread cvm config++ gps)
