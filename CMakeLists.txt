cmake_minimum_required(VERSION 3.20)
project(uds-server C)
set(CMAKE_C_STANDARD 99)

# Library
include(common/CMakeLists.txt)

# Generated diagnostic implementation
include(impl/CMakeLists.txt)


set(SOURCES_COMMON
        src/uds-server.c
        )


add_executable(uds-server
        ${SOURCES_COMMON}
        ${DASHBOARD_LIB_SOURCES}
        ${DIAGNOSTIC_IMPL_SOURCES}
        )

target_compile_definitions(uds-server PRIVATE
        DIAG_STORAGE_ASYNC
        STORAGE_TRACE
        )

target_include_directories(uds-server PRIVATE
        src
        ${DASHBOARD_LIB_INCLUDES}
        ${DIAGNOSTIC_IMPL_INCLUDES}
        )

#target_link_libraries(uds-server PRIVATE
#        pthread
#        m
#        )

add_custom_command(
        TARGET uds-server
        POST_BUILD
        COMMAND $<$<CONFIG:release>:${CMAKE_STRIP}>
        ARGS --strip-all $<TARGET_FILE:uds-server>
)