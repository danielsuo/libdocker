cmake_minimum_required(VERSION 3.5)
project(docker)

set(CMAKE_C_STANDARD 99)
set(DOCKER_INCLUDE_DIR src PARENT_SCOPE)

# Set target name and source files
file (GLOB DOCKER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/**)

add_library(${PROJECT_NAME} ${DOCKER_SOURCE_FILES})

target_link_libraries(
    ${PROJECT_NAME}
    curl
)
