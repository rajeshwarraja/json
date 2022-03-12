list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/modules")
include(PreBuild)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_MakeAvailable(googletest)
endif()

file(GLOB_RECURSE JSON_TEST_SRC src/*.cxx src/*.h)

add_executable(testJson ${JSON_TEST_SRC} "${CMAKE_CURRENT_BINARY_DIR}/version.c")
target_link_libraries(testJson json gtest gtest_main)
target_compile_features(testJson PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(testJson
	XML_OUTPUT_DIR "${CMAKE_BINARY_DIR}/testreports")
