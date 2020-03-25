include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

SET(SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/docker.c
)

add_library( cdockerinterface SHARED ${SRC_FILES})

target_link_libraries(
    cdockerinterface

    -lcurl
)

INSTALL(
    TARGETS cdockerinterface
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)