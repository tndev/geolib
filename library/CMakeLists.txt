 
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
    include/tndev/geo/projection/mercator.hpp
    include/tndev/geo/latlng.distance.hpp
)

add_library(project_warnings INTERFACE)
include_directories(include)

target_compile_options(project_warnings
    INTERFACE
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # warn the user if a variable declaration shadows one from a
                # parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                        # non-virtual destructor. This helps catch hard to
                        # track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual
                            # function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
#        -Wmisleading-indentation # warn if identation implies blocks where blocks
                                # do not exist
#        -Wduplicated-cond # warn if if / else chain has duplicated conditions
#        -Wduplicated-branches # warn if if / else branches have duplicated code
#        -Wlogical-op # warn about logical operations being used where bitwise were
                    # probably wanted
        -Wnull-dereference # warn if a null dereference is detected
#        -Wuseless-cast # warn if you perform a cast to the same type
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output
                # (ie printf)
        -Werror
)


add_library(${project_name} INTERFACE)

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

