if (NOT GTEST_FOUND)
    find_package(GTest REQUIRED)
endif()

find_package(Threads REQUIRED)

if (NOT GMOCK_FOUND)
    find_package(GMock REQUIRED)
endif()

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_utils")
include_directories(
    ${DK_UTILS_INCLUDE_DIRS}
    SYSTEM ${GTEST_INCLUDE_DIRS}
    SYSTEM ${GMOCK_INCLUDE_DIRS}
)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Wno-global-constructors \
        -Wno-missing-prototypes"
    )
endif()

function(add_gtest name sources inc libs)
    add_executable(${name} ${sources})
    add_dependencies(${name} googletest)
    target_link_libraries(${name}
        ${libs}
        ${GMOCK_MAIN_LIBRARY}
        ${GMOCK_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )
    add_test(AllTests ${name})
    target_include_directories(${name} PRIVATE ${inc})
endfunction()

add_gtest(test_exception "test_exception.cpp;${SRC}/exceptions.cpp" ${SRC} "")
add_gtest(test_logger "test_logger.cpp;${SRC}/logger.cpp" ${SRC} "")

if (ENABLE_DK_OPENGL)
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src/dk_opengl")
    set(INC ${SRC} ${EGL_INCLUDE_DIRS})
    set(LINK ${EGL_LIBRARIES})
    add_gtest(test_eglwrapper "test_eglwrapper.cpp;${SRC}/eglwrapper.cpp" "${INC}" ${LINK})
endif()
