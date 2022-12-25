cmake_minimum_required(VERSION 3.24)
project(BowlCalcVer2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest-main)
include_directories (googletest-main/googletest/include)
include_directories (googletest-main/googlemock/include)

set(SOURCE_FILES main.cpp Frame.h Frame.cpp test.cpp test.h)
add_executable(BowlCalcVer2 ${SOURCE_FILES})

target_link_libraries(BowlCalcVer2 gtest gtest_main gmock gmock_main)
