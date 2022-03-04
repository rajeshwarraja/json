cmake_minimum_required(VERSION 3.11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/modules")

project(Json)

include(GitInformation)

display_project_label()

include_directories(include PUBLIC)

add_subdirectory(parser)

add_subdirectory(test)