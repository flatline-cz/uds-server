cmake_minimum_required(VERSION 3.20)
project(uds-server C)
set(CMAKE_C_STANDARD 99)

# Library
include(common/CMakeLists.txt)

# Generated diagnostic implementation
include(impl/CMakeLists.txt)


set(SOURCES_COMMON
        src/uds-server.c
        src/storage-sync.c
        )

if (DEFINED ${EXTERNAL_ISOTP})
else()
    list(APPEND SOURCES_COMMON common/src/iso-tp.c)
endif ()

set(SOURCES_STORAGE
        )

if (DEFINED ${STORAGE_CANBUS_ACCESS})
    list(APPEND SOURCES_STORAGE src/storage-canbus-access.c)
endif ()


add_executable(uds-server
        test/main.c
        test/platform-input.c
        test/platform-output.c
        test/platform-time.c
        ${SOURCES_COMMON}
        ${SOURCES_STORAGE}
        ${DASHBOARD_LIB_SOURCES}
        ${DIAGNOSTIC_IMPL_SOURCES}
        )

target_compile_definitions(uds-server PRIVATE
#        DIAG_STORAGE_ASYNC
        STORAGE_TRACE
#        EXTERNAL_ISOTP
        PROTOCOL_DEBUG
        STORAGE_CANBUS_ACCESS
        PROJECT_NAME="${CMAKE_PROJECT_NAME}"
        )

target_include_directories(uds-server PRIVATE
        include
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