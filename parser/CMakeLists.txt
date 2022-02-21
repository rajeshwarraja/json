cmake_minimum_required(VERSION 3.11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/modules")
project(JsonParser VERSION 1.1.0 LANGUAGES CXX)

include(GetGitVersionInformation)
get_git_version_information(GIT_VERSION)
message(STATUS ${GIT_VERSION})

configure_file(
	"${CMAKE_SOURCE_DIR}/build/version.h.in"
	"${CMAKE_SOURCE_DIR}/parser/src/version.h"
	@ONLY
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE JSON_PARSER_SRC src/*)

add_executable(parser ${JSON_PARSER_SRC})