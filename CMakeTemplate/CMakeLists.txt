cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)

project(hello_cmake)

if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
  message(WARNING "The binary dir of CMake cannot be the same as source dir")
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
  add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

if (NOT MSVC)
  find_program(CCACHE_PROGRAM ccache)
  if (CCACHE_PROGRAM)
    message(STATUS "FOUND CCACHE: ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
  endif()
endif()

add_executable(main main.cpp)
# add_subdirectory(sub_dirs)
