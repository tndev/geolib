function(add_clang_tidy)
  # Setup clang-tidy
  if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_GREATER 3.5)
    set(CMAKE_SUPPORT_CLANG_TIDY TRUE)
  else(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_GREATER 3.5)
    set(CMAKE_SUPPORT_CLANG_TIDY FALSE)
  endif(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_GREATER 3.5)

  if( CMAKE_SUPPORT_CLANG_TIDY )
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)

    cmake_parse_arguments(add_clang_tidy "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    find_program(CLANG_TIDY clang-tidy clang-tidy-mp-3.8)

    IF(CLANG_TIDY)
      message(STATUS "using ${CLANG_TIDY} to for target ${add_clang_tidy_TARGET}.")
      #-google-runtime-int, "-fix"
      set(DO_CLANG_TIDY "${CLANG_TIDY}" )
      set_target_properties(${add_clang_tidy_TARGET} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
    ELSE()
      message(WARNING "clang-tidy was not found")
    ENDIF()
  endif()

endfunction(add_clang_tidy)
