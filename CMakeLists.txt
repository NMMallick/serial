cmake_minimum_required(VERSION 3.0)
project(serial VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

set( serial_SOURCES
  src/Serial.cc
  src/Buffer.cc
  )

add_library(serial SHARED ${serial_SOURCES})

target_include_directories(serial PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )

# TODO: Setup the install interface
install(TARGETS serial
  EXPORT serial
  LIBRARY DESTINATION lib
  )

install(EXPORT serial
  FILE serialConfig.cmake
  NAMESPACE serial::
  DESTINATION lib/serial
  )
