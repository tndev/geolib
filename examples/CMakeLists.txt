 
cmake_minimum_required(VERSION 3.8)

set(project_name "geolib-examples")

project(${project_name})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(${project_name} main.cpp)
target_link_libraries(${project_name} tndev-geolib)


include(ClangFormat)
add_clang_format(TARGET
                 geolib-examples
                 FILES
                 main.cpp)

set_property(TARGET geolib-examples PROPERTY CXX_STANDARD 20)
set_property(TARGET geolib-examples PROPERTY CXX_STANDARD_REQUIRED ON)
