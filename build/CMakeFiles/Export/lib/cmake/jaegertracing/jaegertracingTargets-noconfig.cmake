#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "jaegertracing::jaegertracing" for configuration ""
set_property(TARGET jaegertracing::jaegertracing APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(jaegertracing::jaegertracing PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libjaegertracing.so.0.5.0"
  IMPORTED_SONAME_NOCONFIG "libjaegertracing.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS jaegertracing::jaegertracing )
list(APPEND _IMPORT_CHECK_FILES_FOR_jaegertracing::jaegertracing "${_IMPORT_PREFIX}/lib/libjaegertracing.so.0.5.0" )

# Import target "jaegertracing::jaegertracing-static" for configuration ""
set_property(TARGET jaegertracing::jaegertracing-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(jaegertracing::jaegertracing-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libjaegertracing.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS jaegertracing::jaegertracing-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_jaegertracing::jaegertracing-static "${_IMPORT_PREFIX}/lib/libjaegertracing.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
