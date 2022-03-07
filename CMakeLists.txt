cmake_minimum_required(VERSION 3.16)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/modules")
include(PreBuild)

project(Json)

display_project_label()

include_directories(include PUBLIC)

add_subdirectory(parser)
add_subdirectory(examples)

enable_testing()
add_subdirectory(test)