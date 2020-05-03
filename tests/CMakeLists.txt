 
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
# add_library(project_warnings INTERFACE)

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


SET(SOURCES
  main.cpp
  angle.cpp
  latlng.distance.cpp
  bearing.cpp
  length.cpp
  elevation.cpp
)

add_executable(${project_name}  ${SOURCES})


include(ClangTidy)
add_clang_tidy(TARGET ${project_name})

include(ClangFormat)
add_clang_format(TARGET ${project_name}  FILES ${SOURCES})

include(IncludeWhatYouUse)
add_include_what_you_use(TARGET ${project_name})

target_link_libraries(${project_name} PUBLIC tndev-geolib Catch2::Catch2 PRIVATE project_warnings --coverage)

set_property(TARGET geolib-tests PROPERTY CXX_STANDARD 17)
set_property(TARGET geolib-tests PROPERTY CXX_STANDARD_REQUIRED ON)

include(CTest)
catch_discover_tests(${project_name})
