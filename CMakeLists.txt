cmake_minimum_required(VERSION 3.16.0)

set(project_name "Perception")


project(${project_name})

set(COMPILE_PLATFORM "x86")

set(CMAKE_CXX_STANDARD 14)

message(STATUS "################project ${project_name} start#####################")
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/test)
add_subdirectory(${CMAKE_SOURCE_DIR}/tools)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)