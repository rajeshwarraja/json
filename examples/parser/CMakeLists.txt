include(PreBuild)

display_project_label()

file(GLOB_RECURSE JSON_PARSER_SRC src/*)

add_executable(parser 
	${JSON_PARSER_SRC} 
	"${CMAKE_CURRENT_BINARY_DIR}/version.c")
target_compile_features(parser PRIVATE cxx_std_17)
target_link_libraries(parser json)