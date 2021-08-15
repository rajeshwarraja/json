cmake_minimum_required(VERSION 3.11)
project(JsonParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(src JSON_PARSER_SRC)
add_executable(parser ${JSON_PARSER_SRC})