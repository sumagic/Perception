message(STATUS "################project ${project_name} tools#####################")
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp-dev/include
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/opencv-dev/include/opencv4
)
link_directories(${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp-dev/lib
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/opencv-dev/lib
)

add_executable(perception_offline
    ${CMAKE_SOURCE_DIR}/tools/perception_offline.cc
)

target_link_libraries(perception_offline PRIVATE
    PerceptionCore
    yaml-cpp
    opencv_core
    opencv_imgcodecs
    opencv_imgproc
    opencv_videoio
)
