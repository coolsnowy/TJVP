set(UPLOAD_SRCS
  Upload.cpp
  )

add_executable(cvm-upload ${UPLOAD_SRCS})
target_link_libraries(cvm-upload lcm glib-2.0 pcre pthread cvm paho-mqtt3c-static)

