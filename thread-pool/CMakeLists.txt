cmake_minimum_required(VERSION 2.8)
project(thread-pool)
 
set(CMAKE_BUILD_TYPE "Debug") # Debug/Release
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
 
 add_executable(${PROJECT_NAME} main.cpp)
 target_link_libraries(${PROJECT_NAME} pthread)