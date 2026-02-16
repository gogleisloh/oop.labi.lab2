cmake_minimum_required(VERSION 3.28.3)
project(Twelvee)
set(SOURCE_EXE Twelve.cpp)
find_package(GTest)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runtests  GTest.cpp Twelve.cpp)


target_link_libraries(runtests ${GTEST_LIBRARIES} pthread)


