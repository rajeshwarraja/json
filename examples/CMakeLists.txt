list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/modules")
include(PreBuild)

add_subdirectory(config)
add_subdirectory(parser)