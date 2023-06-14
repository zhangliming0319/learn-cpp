cmake_minimum_required(VERSION 3.1)

project(timer-20ms)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_STANDARD 11)

if(WIN32)
  add_definitions(/utf-8)
  set(LIB_SYS Shlwapi)
elseif(UNIX)
  set(LIB_SYS dl pthread)
endif(WIN32)

add_executable(timer-20ms
  timer-20ms.cpp
)
target_link_libraries(timer-20ms
  ${LIB_SYS} )

