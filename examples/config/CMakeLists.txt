project(JsonConfig)

file(GLOB_RECURSE JSON_PARSER_SRC src/*)

add_executable(config ${JSON_PARSER_SRC})
target_link_libraries(config json)