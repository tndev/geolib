 
cmake_minimum_required(VERSION 3.8)

set(project_name "geolib-tests")
project(${project_name})
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(Catch2)

if(Catch2_FOUND)
  include(Catch)
else()
  add_subdirectory(Catch2)
  include(Catch2/contrib/Catch.cmake)
endif()
enable_testing()


SET(SOURCES
  main.cpp
  angle.cpp
  latlng.distance.cpp
  bearing.cpp
  length.cpp
  elevation.cpp
  projection.cpp
)

add_executable(${project_name}  ${SOURCES})

include(CompilerWarnings)
setup_compiler_warnings(TARGET ${project_name})

include(ClangTidy)
add_clang_tidy(TARGET ${project_name})

include(ClangFormat)
add_clang_format(TARGET ${project_name}  FILES ${SOURCES})

include(IncludeWhatYouUse)
add_include_what_you_use(TARGET ${project_name})

target_link_libraries(${project_name} PUBLIC tndev-geolib Catch2::Catch2 PRIVATE --coverage)

set_property(TARGET geolib-tests PROPERTY CXX_STANDARD 17)
set_property(TARGET geolib-tests PROPERTY CXX_STANDARD_REQUIRED ON)

include(CTest)
catch_discover_tests(${project_name})
