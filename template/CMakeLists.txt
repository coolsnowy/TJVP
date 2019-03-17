set(SRCS
  Template.cpp
  TemplateConfig.cpp
  )

add_executable(cvm-template ${SRCS})
target_link_libraries(cvm-template lcm glib-2.0 pcre pthread config++)
