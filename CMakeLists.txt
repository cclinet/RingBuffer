cmake_minimum_required(VERSION 3.0.0)
project(RingBuffer VERSION 0.1.0)

enable_testing()
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(ring_buffer_test test.cpp)

target_include_directories(ring_buffer_test PRIVATE include)

target_link_libraries(ring_buffer_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ring_buffer_test)
