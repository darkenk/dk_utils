project(dk_utils)
aux_source_directory(./dk_utils SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})
