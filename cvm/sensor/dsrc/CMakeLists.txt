set(SRCS
  Main.cpp
  Dsrc.cpp
  DsrcConfig.cpp
  J2735.cpp
  C-ITS.cpp
  )

add_executable(cvm-dsrc ${SRCS})
target_link_libraries(cvm-dsrc lcm glib-2.0 pcre pthread cvm j2735 C-ITS config++)

add_subdirectory(tests)
