set(SRCS
  ConsoleHMI.cpp
  ConsoleHMIConfig.cpp
  ProtocolMessageDebuger.cpp
  )

add_executable(cvm-consolehmi ${SRCS})
target_link_libraries(cvm-consolehmi lcm glib-2.0 pcre pthread config++)
