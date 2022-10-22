add_library(example)

target_sources(example
  PRIVATE
    example.cpp
  PUBLIC
    example.h
  )

target_include_directories(example
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
# AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux"
message("CMAKE_CXX_COMPILER_ID:" ${CMAKE_CXX_COMPILER_ID})
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  target_compile_options(example
    PUBLIC
      "--coverage"
    )
  target_link_options(example
    INTERFACE
      "--coverage"
    )
endif()
