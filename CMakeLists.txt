cmake_minimum_required(VERSION 2.8)
project(cvm C CXX)

set(CVM_ARCH "x86_64") # arm-linux-gnueabihf or x86_64
set(GCC_MAJOR 5)#4
set(GCC_MINOR 4)#8
set(GCC_VERSION ${GCC_MAJOR}.${GCC_MINOR})

if (${CVM_ARCH} STREQUAL "arm-linux-gnueabihf")
    set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc-${GCC_VERSION})
    set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++-${GCC_VERSION})
elseif(${CVM_ARCH} STREQUAL "x86_64")
    if(0)
        enable_testing()
    endif()
else()
    message("***** Unsupported arch(${CVM_ARCH}) *****")
    return()
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CVM_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})

include_directories(${CVM_ROOT_PATH})
include_directories(${CVM_ROOT_PATH}/thirdpart/include)
include_directories(${CVM_ROOT_PATH}/thirdpart/include/j2735)
include_directories(${CVM_ROOT_PATH}/thirdpart/include/C-ITS)
include_directories(${CVM_ROOT_PATH}/thirdpart/include/glib)

link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/libconfig)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/lcm)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/gps)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/j2735)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/C-ITS)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/glib)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/paho-mqtt)
link_directories(${CVM_ROOT_PATH}/thirdpart/lib/${CVM_ARCH}-${GCC_VERSION}/cjson)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CVM_ROOT_PATH}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CVM_ROOT_PATH}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CVM_ROOT_PATH}/lib)

add_subdirectory(cvm)

