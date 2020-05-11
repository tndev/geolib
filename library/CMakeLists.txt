 
cmake_minimum_required(VERSION 3.8)

set(project_name "tndev-geolib")
project(${project_name} LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)



SET(HEADERS
    include/tndev/geo/angle.hpp
    include/tndev/geo/constants.hpp
    include/tndev/geo/latlng.hpp
    include/tndev/geo/latlng_elevation.hpp
    include/tndev/geo/bearing.hpp
    include/tndev/geo/length.hpp
    include/tndev/geo/extent.hpp
    include/tndev/geo/point.hpp
    include/tndev/geo/quadkey.hpp
    include/tndev/geo/tile.hpp
    include/tndev/geo/bounding_box.hpp
    include/tndev/geo/projection/mercator.hpp
    include/tndev/geo/latlng.distance.hpp
)

include_directories(include)

add_library(${project_name} INTERFACE)

include(CompilerWarnings)
setup_compiler_warnings(TARGET ${project_name})

target_include_directories(
  ${project_name}
    INTERFACE 
      $<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)


include(ClangFormat)
add_clang_format(TARGET
                 ${project_name}
                 FILES
                 ${HEADERS})

include(ClangTidy)

