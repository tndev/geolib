 
cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(tndevgeo)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"  ${CMAKE_MODULE_PATH})


option(TNDEVGEO_BUILD_TESTS "build tndevgeo tests" NO)
option(TNDEVGEO_BUILD_EXAMPLES "build tndevgeo examples" NO)

add_subdirectory(library)

if(TNDEVGEO_BUILD_TESTS)
add_subdirectory(tests)
endif()

if(TNDEVGEO_BUILD_EXAMPLES)
add_subdirectory(examples)
endif()