function(add_include_what_you_use)

find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)

if(INCLUDE_WHAT_YOU_USE)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)

    cmake_parse_arguments(add_include_what_you_use "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set_property(TARGET ${add_include_what_you_use_TARGET} PROPERTY CXX_INCLUDE_WHAT_YOU_USE /usr/bin/include-what-you-use)
else()
    message(WARNING "include-what-you-use was not found")
endif()
endfunction(add_include_what_you_use)