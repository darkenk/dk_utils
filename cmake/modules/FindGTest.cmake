if(NOT DEFINED ${GTEST_FOUND})

include(ExternalProject)

set(GTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(GMOCK_LIB_DIR ${GTEST_ROOT}/src/googletest-build/googlemock)
set(GTEST_LIB_DIR ${GTEST_ROOT}/src/googletest-build/googlemock/gtest)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    # Disable update in every run
    UPDATE_COMMAND ""
    CMAKE_ARGS -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
               -Dgtest_force_shared_crt=ON
               -DBUILD_GTEST=ON
    PREFIX ${GTEST_ROOT}

    # Disable install step
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${GMOCK_LIB_DIR}/libgmock_main.a
                     ${GMOCK_LIB_DIR}/libgmock.a
                     ${GTEST_LIB_DIR}/libgtest.a
                     ${GTEST_LIB_DIR}/libgtest_main.a
)

set(GTEST_FOUND 1 CACHE STRING "GTEST_FOUND")
set(GMOCK_FOUND 1 CACHE STRING "GMOCK_FOUND")

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include CACHE STRING "GTEST path")
set(GMOCK_INCLUDE_DIRS ${source_dir}/googlemock/include CACHE STRING "GMOCK path")

macro(dk_add_lib variable_name library_name library_path)
    add_library(${library_name} STATIC IMPORTED GLOBAL)
    set_target_properties(${library_name} PROPERTIES IMPORTED_LOCATION ${library_path})
    add_dependencies(${library_name} googletest)
    set(${variable_name} ${library_name} CACHE STRING "${library_name}")
endmacro()

dk_add_lib(GMOCK_LIBRARY gmock ${GMOCK_LIB_DIR}/libgmock.a)
dk_add_lib(GMOCK_MAIN_LIBRARY gmock_main ${GMOCK_LIB_DIR}/libgmock_main.a)
dk_add_lib(GTEST_LIBRARY gtest ${GTEST_LIB_DIR}/libgtest.a)
dk_add_lib(GTEST_MAIN_LIBRARY gtest_main ${GTEST_LIB_DIR}/libgtest_main.a)

find_package(Threads REQUIRED)

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

endif()
