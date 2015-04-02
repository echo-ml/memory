cmake_minimum_required(VERSION 3.0)

project("echo-memory")

enable_testing()

include(Echo/Test)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB headers
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/echo/*.h"
)

file(GLOB memory-headers
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/echo/memory/*.h"
)

file(GLOB unittests
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/unittest/*_test.cpp"
)


install(FILES ${headers} DESTINATION include/echo)
install(FILES ${memory-headers} DESTINATION include/echo/memory)

add_catch_test(memory-test ${unittests})
