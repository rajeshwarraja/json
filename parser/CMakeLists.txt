cmake_minimum_required(VERSION 3.11)
project(JsonParser VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(
	"${CMAKE_SOURCE_DIR}/build/version.c.in"
	"${CMAKE_CURRENT_BINARY_DIR}/version.c"
	@ONLY
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE JSON_PARSER_SRC src/*)

add_executable(parser 
	${JSON_PARSER_SRC} 
	"${CMAKE_CURRENT_BINARY_DIR}/version.c")