cmake_minimum_required(VERSION 3.2)
project(format)
 
#set(CMAKE_BUILD_TYPE "Debug") # Debug/Release
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)
