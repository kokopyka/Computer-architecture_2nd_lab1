cmake_minimum_required(VERSION 3.2)
project(CA_2nd_lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BigNumbers.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/oleh/ClionProjects/Computer-architecture-2nd-lab1/") # to read data.txt <---- look here
add_executable(CA_2nd_lab1 ${SOURCE_FILES})