set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_utils")

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/gtest_tools.cmake)

add_gtest(test_exception "test_exception.cpp;${SRC}/exceptions.cpp" ${SRC} "")
add_gtest(test_logger "test_logger.cpp;${SRC}/logger.cpp" ${SRC} "")
add_gtest(test_observer "test_observer.cpp;${SRC}/observer.cpp" ${SRC} "")

if (ENABLE_DK_OPENGL)
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_opengl")
    set(INC ${SRC}/../ ${EGL_INCLUDE_DIRS})
    set(LINK ${EGL_LIBRARIES})
    add_gtest(test_eglwrapper "test_eglwrapper.cpp;${SRC}/eglwrapper.cpp" "${INC}" ${LINK})
endif()

if (ENABLE_DK_X11)
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_opengl")
    set(INC ${SRC}/../ ${XCB_INCLUDE_DIRS})
    set(LINK "${XCB_LIBRARIES}")
    add_gtest(test_windowx11 "test_windowx11.cpp;${SRC}/windowx11.cpp" "${INC}" "${LINK}")
endif()
