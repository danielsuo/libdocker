cmake_minimum_required(VERSION 3.6)
project(libdocker)

set(CMAKE_C_STANDARD 99)

# Set target name and source files
file (GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/**)

add_library(libdocker ${SOURCE_FILES})

target_link_libraries(
    libdocker
    curl
)