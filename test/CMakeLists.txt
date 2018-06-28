cmake_minimum_required(VERSION 3.2.2)

project(SensorPreFusion_test VERSION 1.0.0)

set(SOURCE test.cpp)

set(SRC_COMMON
    ../common/SensorData.cpp
    ../common/SensorData.h
    ../common/Coordinates.cpp
    ../common/Coordinates.h)

set(SRC_DRIVEASSISTANCE
    ../driveassistance/SensorPreFusion.cpp
    ../driveassistance/SensorPreFusion.h
    ../driveassistance/RuntimeEnvironment.cpp
    ../driveassistance/RuntimeEnvironment.h)

set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX11_EXTENSION_COMPILE_OPTION}")

list(APPEND ALL_FILES
    ${SOURCE}
    ${SRC_COMMON}
    ${SRC_UTILS})

add_executable(SensorPreFusion_test ${ALL_FILES})
