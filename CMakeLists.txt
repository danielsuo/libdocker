cmake_minimum_required(VERSION 3.6)
project(libdocker)

set(CMAKE_C_STANDARD 99)

# Set target name and source files
set (TARGET_NAME ${CMAKE_PROJECT_NAME})
file (GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/**)

add_library(${TARGET_NAME} ${SOURCE_FILES})

target_link_libraries(
    ${TARGET_NAME}
    curl
)