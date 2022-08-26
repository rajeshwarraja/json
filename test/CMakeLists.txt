project(JsonTest)

option(INSTALL_GTEST OFF)
option(BUILD_GMOCK OFF)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.12.0)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_MakeAvailable(googletest)
endif()

file(GLOB_RECURSE JSON_TEST_SRC src/*.cxx src/*.h)

add_executable(testJson ${JSON_TEST_SRC})
target_link_libraries(testJson json gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(testJson
	XML_OUTPUT_DIR "${CMAKE_BINARY_DIR}/testreports")