cmake_minimum_required(VERSION 3.2.2)

project(SensorPreFusion VERSION 1.0.0)

find_package(Threads)
find_package(Doxygen)

if(DOXYGEN_FOUND)
    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

OPTION(BUILD_CATCH "Build catch tests" OFF)

set(SOURCE main.cpp)
aux_source_directory(common SRC_COMMON)
aux_source_directory(driverassistance SRC_DRIVERASSISTANCE)
if (BUILD_CATCH)
    add_subdirectory(test)
endif()

list(APPEND ALL_FILES
    ${SOURCE}
    ${SRC_COMMON}
    ${SRC_DRIVERASSISTANCE})

include_directories(SensorPreFusion PRIVATE common)

set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX11_EXTENSION_COMPILE_OPTION} -pthread")

add_executable(SensorPreFusion ${ALL_FILES})
