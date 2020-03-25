# cmake version
cmake_minimum_required(VERSION 3.5)

#cmake policy
cmake_policy(SET CMP0015 NEW)

# Project name.
project(cdocker)

# Setting options.
option(EXAMPLE_BUILD "Build using examples" ON)

set( CMAKE_INSTALL_LIBDIR /usr/lib )
set( CMAKE_INSTALL_BINDIR /usr/bin )

find_package(CURL REQUIRED)


# Install docker.h to the /usr/include directory
install(FILES source_code/CDOCKER/inc/docker.h PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION /usr/include)


add_subdirectory(./source_code)
if(EXAMPLE_BUILD)
	add_subdirectory(./example)
endif(EXAMPLE_BUILD)

# Adding deb package build options.
set(CPACK_PACKAGE_NAME "cdocker")
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
