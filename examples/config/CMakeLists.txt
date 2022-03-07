file(GLOB_RECURSE JSON_PARSER_SRC src/*)

add_executable(config ${JSON_PARSER_SRC} ${CMAKE_BINARY_DIR}/version.c)
target_compile_features(config PRIVATE cxx_std_17)