cmake_minimum_required(VERSION 3.20)

project(Json)

add_library(json INTERFACE)
target_include_directories(json INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include>)
target_compile_features(json INTERFACE cxx_std_17)

add_subdirectory(examples)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    enable_testing()
    add_subdirectory(test)
endif()

install(DIRECTORY include/ DESTINATION include)
install(TARGETS json EXPORT Json)
install(EXPORT Json DESTINATION cmake)