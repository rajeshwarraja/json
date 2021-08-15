cmake_minimum_required(VERSION 3.11)
project(Json VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include PUBLIC)

aux_source_directory(lib JSON_LIB_SRC)
add_library(json SHARED ${JSON_LIB_SRC})

aux_source_directory(src JSON_SRC)
add_executable(jsonexample ${JSON_SRC})

enable_testing()

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

aux_source_directory(test JSON_TEST_SRC)
add_executable(testJson ${JSON_TEST_SRC})
target_link_libraries(testJson gtest gtest_main)

find_package(GTest QUIET)
if(GTest_FOUND)
  gtest_discover_tests(testJson)
else()
  add_test(testJson testJson)
endif()