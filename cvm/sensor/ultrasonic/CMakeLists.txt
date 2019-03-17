set(SRCS
  Main.cpp
  Ultrasonic.cpp
  UltrasonicConfig.cpp
  )

add_executable(cvm-ultrasonic ${SRCS})
target_link_libraries(cvm-ultrasonic lcm glib-2.0 pcre pthread config++)
