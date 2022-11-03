cmake_minimum_required(VERSION 2.8)
project(glog-gflags)
 
#set(CMAKE_BUILD_TYPE "Debug") # Debug/Release
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
 
find_package(gflags REQUIRED)
include_directories(${gflags_INCLUDE_DIR})
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})
 
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glog gflags)