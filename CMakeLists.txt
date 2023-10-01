
cmake_minimum_required(VERSION 3.15)

project(kod
  VERSION 1.0.0
  DESCRIPTION "The Kod library"
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SOURCES
  src/value.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_subdirectory(tests)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h")
