function(setup_compiler_warnings)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)

    cmake_parse_arguments(setup_compiler_warnings "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    SET(compiler_warnings ${setup_compiler_warnings_TARGET}_warnings)
    

    #add_library(${compiler_warnings} INTERFACE)

    add_compile_options(${setup_compiler_warnings_TARGET}
        #PUBLIC
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


    # if (MSVC)
    # # warning level 4 and all warnings as errors
    # add_compile_options(/W4 /WX)
    # else()
    # # lots of warnings and all warnings as errors
    # add_compile_options(-Wall -Wextra -pedantic -Werror)
    # endif()


endfunction(setup_compiler_warnings)