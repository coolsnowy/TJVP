add_executable(channel_test Channel_test.cpp)
target_link_libraries(channel_test cvm pthread)

#add_executable(eventloop_unittest EventLoop_unittest.cpp)
#target_link_libraries(eventloop_unittest cvm_base pthread)

add_executable(timerqueue_unittest TimerQueue_unittest.cpp)
target_link_libraries(timerqueue_unittest cvm)

add_executable(TimestampTest TimestampTest.cpp)
target_link_libraries(TimestampTest cvm ${GTEST_BOTH_LIBRARIES} pthread)
add_test(TimestampTest TimestampTest)

add_executable(fileloggertest FileLoggerTest.cpp)
target_link_libraries(fileloggertest cvm)
