project(dk_utils)
cmake_minimum_required(VERSION 3.2.1)

# set build type to debug as it is in development phase
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE DEBUG CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# enable verbose building
if (NOT CMAKE_VERBOSE_MAKEFILE)
    set(CMAKE_VERBOSE_MAKEFILE ON CACHE STRING "Enable compile verbose mode by default" FORCE)
endif()

include(cmake/CMakeLists.txt)

option(ENABLE_TESTS "enable tests" ON)
if (ENABLE_TESTS)
    add_subdirectory(ext/gtest)
    add_subdirectory(tests)
endif()

add_subdirectory(src)
