if (NOT GTEST_FOUND)
    find_package(GTest REQUIRED)
endif()

find_package(Threads REQUIRED)

if (NOT GMOCK_FOUND)
    find_package(GMock REQUIRED)
endif()

set(SRC "${CMAKE_SOURCE_DIR}/src/dk_utils")
include_directories(${SRC}
    SYSTEM ${GTEST_INCLUDE_DIRS}
    SYSTEM ${GMOCK_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wno-global-constructors \
    -Wno-missing-prototypes"
)

function(add_gtest name sources)
    add_executable(${name} ${sources})
    add_dependencies(${name} googletest)
    target_link_libraries(${name}
        ${GMOCK_MAIN_LIBRARY}
        ${GMOCK_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )
    add_test(AllTests ${name})
endfunction()

add_gtest(test_exception "test_exception.cpp;${SRC}/exceptions.cpp")
add_gtest(test_logger "test_logger.cpp;${SRC}/logger.cpp")
