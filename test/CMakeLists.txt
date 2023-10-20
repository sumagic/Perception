message(STATUS "################project ${project_name} unittest start#####################")
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/googletest-dev/include
    ${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/yaml-cpp/include
)
link_directories(${CMAKE_SOURCE_DIR}/lib/${COMPILE_PLATFORM}/googletest-dev/lib)

add_executable(perception_ut
    ${CMAKE_SOURCE_DIR}/test/unittest_main.cc
    ${CMAKE_SOURCE_DIR}/test/utils/log_unittest.cc
)

target_link_libraries(perception_ut PRIVATE
    gmock
    gmock_main
    gtest
    gtest_main
)

enable_testing()