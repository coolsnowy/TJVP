set(SRCS
  Main.cpp
  MillimeterWave.cpp
  MillimeterWaveConfig.cpp
  )

add_executable(cvm-millimeterwave ${SRCS})
target_link_libraries(cvm-millimeterwave lcm glib-2.0 pcre pthread config++)
