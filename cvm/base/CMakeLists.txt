set(SRCS
  Channel.cpp
  EventLoop.cpp
  FileLogger.cpp
  Logging.cpp
  Timestamp.cpp
  Poller.cpp
  Utils.cpp
  TimerQueue.cpp
  CountDownLatch.cpp
  )

add_library(cvm ${SRCS})
#add_subdirectory(tests)

