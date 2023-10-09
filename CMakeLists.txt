
cmake_minimum_required(VERSION 3.15)

project(kod
  VERSION 1.0.0
  DESCRIPTION "The Kod Library"
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)

if(MSVC)
  add_compile_options(/W4 /WX)
  add_definitions(-DKOD_API_DLLEXPORT)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SOURCES
  src/memory.c
  src/status.c
  src/string.c
  src/utils.c
  src/value.c)

set(STATIC_LIB ${PROJECT_NAME}-static)
set(SHARED_LIB ${PROJECT_NAME}-shared)

add_library(${STATIC_LIB} STATIC ${SOURCES})
add_library(${SHARED_LIB} SHARED ${SOURCES})

set_target_properties(${STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_subdirectory(tests)

include(GNUInstallDirs)

install(TARGETS ${STATIC_LIB} ${SHARED_LIB}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h*")
