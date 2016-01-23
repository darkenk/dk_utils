set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_utils")

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ToolsGtest.txt)

add_gtest(test_exception "test_exception.cpp;${SRC}/exceptions.cpp" ${SRC} "")
add_gtest(test_logger "test_logger.cpp;${SRC}/logger.cpp" ${SRC} "")

if (ENABLE_DK_OPENGL)
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_opengl")
    set(INC ${SRC} ${EGL_INCLUDE_DIRS})
    set(LINK ${EGL_LIBRARIES})
    add_gtest(test_eglwrapper "test_eglwrapper.cpp;${SRC}/eglwrapper.cpp" "${INC}" ${LINK})
endif()
