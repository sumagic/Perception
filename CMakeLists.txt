cmake_minimum_required(VERSION 3.16.0)

set(project_name "Perception")


project(${project_name})

set(COMPILE_PLATFORM "aarch64")
set(COMPILE_PLATFORM "x86")

set(CMAKE_SYSTEM_NAME Linux)

set(ECARX_ENGINE_PATH "/home/geely/kx/ecarx-ai-sdk/ecarx/ecarxengine")

if (${COMPILE_PLATFORM} STREQUAL "aarch64")
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
endif()

set(CMAKE_CXX_STANDARD 14)
add_definitions(-g)

message(STATUS "################project ${project_name} start#####################")
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_SOURCE_DIR}/tools)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)