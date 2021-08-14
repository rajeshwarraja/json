project(Json)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include PUBLIC)

aux_source_directory(lib JSON_LIB_SRC)
add_library(json SHARED ${JSON_LIB_SRC})

aux_source_directory(src JSON_SRC)
add_executable(jsonexample ${JSON_SRC})
target_link_libraries(json dl -rdynamic)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
aux_source_directory(test JSON_TEST_SRC)
add_executable(test ${JSON_TEST_SRC})
target_link_libraries(test GTest::gtest GTest::gtest_main)

gtest_discover_tests(test)