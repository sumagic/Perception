message(STATUS "################project ${project_name} core #####################")

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp/include
)
link_directories(${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp/lib)

add_library(PerceptionCore SHARED
    operator/sub_mean_scale.cc
    utils/file.cc
)

target_link_libraries(PerceptionCore PRIVATE
    yaml-cpp
)