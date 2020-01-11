function(add_clang_format)
  set(options)
  set(oneValueArgs TARGET STYLE)
  set(multiValueArgs FILES)

  cmake_parse_arguments(add_code_format "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  list(REMOVE_DUPLICATES add_code_format_FILES)
  list(SORT add_code_format_FILES)

  find_program(CLANG_FORMAT clang-format clang-format-mp-3.8)


  IF(CLANG_FORMAT)

    message(STATUS "using ${CLANG_FORMAT} to format code.")

    add_custom_target( "${add_code_format_TARGET}_clangformat"
      COMMAND ${CLANG_FORMAT}
        # "-style=${add_code_format_STYLE}"
        "-i" ${add_code_format_FILES}
      DEPENDS ${add_code_format_FILES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      VERBATIM
    )

    add_dependencies( ${add_code_format_TARGET} "${add_code_format_TARGET}_clangformat" )
  ELSE()
    message(WARNING "clang-format was not found")
  ENDIF()

endfunction(add_clang_format)
