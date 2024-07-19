cmake_minimum_required(VERSION 3.15.2)
project(demoapps LANGUAGES CXX)

# If no CMAKE_PREFIX_PATH was provided, add the expected location
# relative to the examples
if (NOT CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif()

message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")

if (NOT CMAKE_CXX_STANDARD)
    set (CMAKE_CXX_STANDARD 11)
endif()

message(STATUS "CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")

if (CMAKE_CXX_STANDARD LESS 11 OR CMAKE_CXX_STANDARD EQUAL 98)
  message(FATAL_ERROR "CMAKE_CXX_STANDARD>=11 is required")
endif ()
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Blpapi
find_package(blpapi REQUIRED CONFIG)

if(NOT WIN32)
  # The blpapi shared object currently does not define an "soname", and we
  # need to inform cmake of that. Otherwise, the linker will use the file
  # path to the shared object as the name in the dependency list, which will
  # later on cause the loader to exclusively use that file path and disregard
  # 'LD_LIBRARY_PATH' (this is the behavior of the loader when it sees a '/'
  # in the name of a dependency).
  set_property(TARGET blpapi PROPERTY IMPORTED_NO_SONAME TRUE)
endif()

# If not specified, build with Release configuration
# for non-windows architectures.
if(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "CMAKE_BUILD_TYPE not provided, using `Release` as default")
endif()

# If not specified, build for current machine architecture.
math(EXPR _ARCH "8 * ${CMAKE_SIZEOF_VOID_P}")

function(configure_example_target TARGET)
  add_executable(${TARGET} ${TARGET}.cpp)
  target_include_directories(
    ${TARGET} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

  set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME "${TARGET}_${_ARCH}")

  if(WIN32)
    target_compile_definitions(${TARGET} PUBLIC _CRT_SECURE_NO_WARNINGS)
  else()
    target_compile_definitions(${TARGET} PUBLIC _POSIX_PTHREAD_SEMANTICS)

  endif()

  target_link_libraries(${TARGET} PUBLIC blpapi)

  install(TARGETS ${TARGET}
    DESTINATION "${OUTPUT_DIR}"
    COMPONENT "demoapps")
endfunction()

file(STRINGS "examples.list" EXAMPLES)

foreach(EXAMPLE ${EXAMPLES})
    configure_example_target(${EXAMPLE})
endforeach(${EXAMPLE})
