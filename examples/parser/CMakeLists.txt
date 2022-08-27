project(JsonParser)

file(GLOB_RECURSE JSON_PARSER_SRC src/*)

add_executable(parser 
	${JSON_PARSER_SRC})
target_link_libraries(parser json)