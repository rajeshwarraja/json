if(WIN32)
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")
  set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG")
endif()

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

file(GLOB_RECURSE JSON_TEST_SRC src/*.cxx src/*.h)
add_executable(testJson ${JSON_TEST_SRC})
target_link_libraries(testJson gtest gtest_main)
target_compile_features(testJson PRIVATE cxx_std_17)

enable_testing()

find_package(GTest QUIET)
if(GTest_FOUND)
  gtest_discover_tests(testJson)
else()
  add_test(testJson testJson)
endif()