if (NOT dk_utils_FOUND)
    set(lib dk_utils)
    string(TOUPPER ${lib} upper_lib)
    set(${upper_lib}_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/src)
    set(${upper_lib}_LIBRARIES ${lib} CACHE INTERNAL "${lib} library" FORCE)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(${lib} DEFAULT_MSG
                                      ${upper_lib}_LIBRARIES ${upper_lib}_INCLUDE_DIRS)
    mark_as_advanced(${upper_lib}_INCLUDE_DIRS ${upper_lib}_LIBRARIES)
    if (NOT TARGET ${lib})
        set(ENABLE_TESTS OFF CACHE BOOL "Disable dk_utils tests" FORCE)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_BINARY_DIR}/${lib})
    endif()
    set(CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/cmake/modules
        ${CMAKE_CURRENT_LIST_DIR}/cmake/tools
        ${CMAKE_MODULE_PATH}
    )
endif()
