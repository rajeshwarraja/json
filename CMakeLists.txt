cmake_minimum_required(VERSION 3.11)
project(Json VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include PUBLIC)

aux_source_directory(lib JSON_LIB_SRC)
add_library(json SHARED ${JSON_LIB_SRC})

enable_testing()
add_subdirectory(test)