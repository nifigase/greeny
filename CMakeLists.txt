cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -Wno-deprecated"
  CACHE
  INTERNAL "Flags used by the compiler during all builds"
  )

set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0"
  CACHE
  INTERNAL "Flags used by the compiler during debug builds"
  )

set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/bin
)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(test
  test.cpp
  Greeny.cpp
)
