message(STATUS "################project ${project_name} core #####################")

add_definitions(-DUSE_NCNN)

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp-dev/include
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/Eigen/include/eigen3
    ${ECARX_ENGINE_PATH}/include
)

link_directories(${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp-dev/lib
)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/ncnn/include
)

add_library(PerceptionCore SHARED
    operator/sub_mean_scale.cc
    operator/letter_box.cc
    operator/yolov5_decoder.cc
    operator/predbox_nms.cc
    utils/file.cc
    ai_engine/ncnn.cc
    ai_engine/ecarx_engine.cc
)

if(${COMPILE_PLATFORM} STREQUAL "x86")
    target_link_directories(PerceptionCore 
        PUBLIC ${ECARX_ENGINE_PATH}/lib/linux_x86
    )
else()
    target_link_directories(PerceptionCore
        PUBLIC ${ECARX_ENGINE_PATH}/lib/linux_arm
    )
endif()

target_link_directories(PerceptionCore
    PUBLIC ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/ncnn/lib
)

target_link_libraries(PerceptionCore
    yaml-cpp
    ecarx_engine
    ncnn
)