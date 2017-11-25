project(Twiddle)

cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(sources src/Robot.cpp src/Robot.h src/Twiddle.h src/TestTwiddle.cpp src/main.cpp)

add_executable(twiddle ${sources})

