set(SRCS
  Main.cpp
  Can.cpp
  CanConfig.cpp
  CanTransmitterFactory.cpp
  CanDecoderFactory.cpp
  decoder/RoeweE50CanDecoder.cpp
  decoder/PanAsiaCanDecoder.cpp
  decoder/BaicCanDecoder.cpp
  transmitter/SocketCanTransmitter.cpp
  )

add_executable(cvm-can ${SRCS})
target_link_libraries(cvm-can lcm glib-2.0 pcre pthread cvm config++)
