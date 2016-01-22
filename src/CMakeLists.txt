project(dk_utils)
aux_source_directory(./dk_utils SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})
set(DK_UTILS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "DK_UTILS path")
