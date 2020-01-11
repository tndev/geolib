 
cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(tndevgeo)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"  ${CMAKE_MODULE_PATH})

add_subdirectory(library)
add_subdirectory(tests)
add_subdirectory(examples)
