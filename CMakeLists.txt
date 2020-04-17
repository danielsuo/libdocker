# cmake version
cmake_minimum_required(VERSION 3.5)

#cmake policy
cmake_policy(SET CMP0015 NEW)

# Project name.
project(docker)

# Setting options.
option(EXAMPLE_BUILD "Build using examples" ON)

set( CMAKE_INSTALL_LIBDIR /usr/lib )
set( CMAKE_INSTALL_BINDIR /usr/bin )

find_package(CURL REQUIRED)


# Install docker.h to the /usr/include directory
install(FILES inc/docker.h PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION /usr/include)

# Including the headers to be used for building the SDK.
include_directories(${CMAKE_CURRENT_LIST_DIR}/inc)

# The source files.
SET(SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/docker.c
)

# The cdocker will be created as a .so
add_library( docker SHARED ${SRC_FILES})

# Linking with dependencies.
target_link_libraries(
    docker

    -lcurl
)

# Installing in the target file as a library.
INSTALL(
    TARGETS docker
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)

# If example build is enabled.
if(EXAMPLE_BUILD)
    include_directories(${CMAKE_SOURCE_DIR}/inc)

    SET( SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/example/example.c
    )

    add_executable(docker_example ${SRC_FILES})

    target_link_libraries(
        docker_example
        docker
    )

    install(TARGETS docker_example RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif(EXAMPLE_BUILD)

# Adding deb package build options.
set(CPACK_PACKAGE_NAME "docker_c_sdk")
set(CDOCKER_VERSION_MAJOR 1)
set(CDOCKER_VERSION_MINOR 0)
set(CDOCKER_VERSION_PATCH 0)

set(CPACK_PACKAGE_VERSION_MAJOR "${CDOCKER_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CDOCKER_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CDOCKER_VERSION_PATCH}")

set(CPACK_DEBIAN_PACKAGE_SHIPBUILDS ON)

set(CPACK_GENERATOR "DEB")

set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "schaffung")

include(CPack)
