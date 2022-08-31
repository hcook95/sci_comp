cmake_minimum_required(VERSION 3.12)
project(Array2D CXX)

# Options
option(ENABLE_TESTS "Build tests" ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Testing
if(ENABLE_TESTS)
    find_package(Catch2 REQUIRED)
    add_executable(test_array2d test_array2d.cc array2d.hh)
    target_link_libraries(test_array2d PRIVATE Catch2::Catch2)
    include(CTest)
    include(Catch)
    catch_discover_tests(test_array2d)
endif()
