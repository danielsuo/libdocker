include_directories(${CMAKE_CURRENT_LIST_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/source_code/CDOCKER/inc)

SET( SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/example.c
)

add_executable(cdockerinterfaceexample ${SRC_FILES})

target_link_libraries(
    cdockerinterfaceexample
    cdockerinterface
)

install(TARGETS cdockerinterfaceexample RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
