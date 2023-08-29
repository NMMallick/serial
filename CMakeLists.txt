cmake_minimum_required(VERSION 3.0)
project(serial VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_EXAMPLES ON)

set( serial_SOURCES
  src/Serial.cc
  src/Buffer.cc
  )

add_library(serial SHARED ${serial_SOURCES})

target_include_directories(serial PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )


if (BUILD_EXAMPLES)
  add_executable(test examples/test.cc)
  target_link_libraries(test PUBLIC serial)
endif()

if (BUILD_TESTS)
  find_package(Catch2 3 REQUIRED)
  add_executable(construct_serial tests/construction.cc)
  target_link_libraries(construct_serial PRIVATE Catch2::Catch2WithMain serial)
endif()

# TODO: Setup the install interface
install(TARGETS serial
  EXPORT serial
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
  )

install(DIRECTORY include/serial
  DESTINATION include)

install(EXPORT serial
  FILE serialConfig.cmake
  NAMESPACE serial::
  DESTINATION cmake
  )
