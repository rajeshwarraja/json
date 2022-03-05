cmake_minimum_required(VERSION 3.16)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/modules")
include(GitInformation)

project(Json)

display_project_label()

include_directories(include PUBLIC)

add_subdirectory(parser)


enable_testing()
add_subdirectory(test)