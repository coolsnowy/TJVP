set(Logger_SRCS
  LcmLogger.cpp
  )

set(Player_SRCS
  LcmLogplayer.cpp
  )

add_executable(cvm-logger ${Logger_SRCS})
target_link_libraries(cvm-logger cvm lcm glib-2.0 pcre pthread)

add_executable(cvm-player ${Player_SRCS})
target_link_libraries(cvm-player cvm lcm glib-2.0 pcre pthread)
