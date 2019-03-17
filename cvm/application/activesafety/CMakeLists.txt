set(SRCS
  Main.cpp
  ActiveSafety.cpp
  ActiveSafetyConfig.cpp
  CollisionDetec.cpp
  ComputeTools.cpp
  )

add_executable(cvm-app-safety ${SRCS})
target_link_libraries(cvm-app-safety lcm glib-2.0 pcre pthread cvm)
