find_library(GLESv2_LIBRARIES NAMES GLESv2)
find_path(GLESv2_INCLUDE_DIRS NAMES GLES2/gl2.h     )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLESv2 DEFAULT_MSG GLESv2_LIBRARIES GLESv2_INCLUDE_DIRS)

mark_as_advanced(GLESv2_INCLUDE_DIRS GLESv2_LIBRARIES)
