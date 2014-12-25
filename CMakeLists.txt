cmake_minimum_required(VERSION 2.8.4)
project(haffman)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/haffman.cpp)
add_executable(haffman ${SOURCE_FILES})