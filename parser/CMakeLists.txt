get_git_assembly_version(GIT_VERSION)
get_git_commit(GIT_HASH)
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
target_compile_features(parser PRIVATE cxx_std_17)