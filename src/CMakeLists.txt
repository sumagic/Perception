message(STATUS "################project ${project_name} core #####################")

add_definitions(-DUSE_NCNN)

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp-dev/include
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/Eigen/include/eigen3
)
link_directories(${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp-dev/lib
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/ncnn/lib
)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/ncnn/include
)

add_library(PerceptionCore SHARED
    operator/sub_mean_scale.cc
    operator/yolov5_decoder.cc
    utils/file.cc
    ai_engine/ncnn.cc
)

target_link_libraries(PerceptionCore PRIVATE
    yaml-cpp
    ncnn
)