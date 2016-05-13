project(dk_utils)
aux_source_directory(./dk_utils SRC)
if(ENABLE_DK_OPENGL)
    set(SRC ${SRC}
        ./dk_opengl/eglwrapper.cpp
    )
    include_directories(
        SYSTEM ${EGL_INCLUDE_DIRS}
        ${GLESv2_INCLUDE_DIRS}
    )
endif()

add_library(${PROJECT_NAME} STATIC ${SRC})
set(DK_UTILS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "DK_UTILS path")
