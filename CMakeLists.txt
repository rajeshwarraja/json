cmake_minimum_required(VERSION 3.18)

project(Json)

add_library(json INTERFACE)
target_include_directories(json INTERFACE include/)
target_compile_features(json INTERFACE cxx_std_17)

if(JSON_CI_PIPELINE)
	add_subdirectory(examples)

	enable_testing()
	add_subdirectory(test)
endif()