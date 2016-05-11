cmake_policy(SET CMP0048 NEW)
project(dk_utils VERSION 0.1)
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

include(cmake/compiler_flags.cmake)
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/;${ECM_MODULE_PATH};\
    ${CMAKE_MODULE_PATH}")

message(${CMAKE_MODULE_PATH})

find_package(EGL)
find_package(OpenGLES2)
if (EGL_FOUND)
    set(ENABLE_DK_OPENGL "true")
endif()

find_package(XCB COMPONENTS ICCCM)
if (XCB_FOUND)
    set(ENABLE_DK_X11 "true")
endif()

option(ENABLE_TESTS "enable tests" ON)
if (ENABLE_TESTS)
    add_subdirectory(ext/gtest)
    add_subdirectory(tests)
endif()

add_subdirectory(src)
