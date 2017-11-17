set(name Welcome)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++11")
project(${name})
#find_package(OpenCV REQUIRED)
add_executable(${name} main.cpp colormod.h)
#target_link_libraries(${name} ${OpenCV_LIBS})
