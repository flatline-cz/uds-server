cmake_minimum_required(VERSION 3.21)

set(PLATFORM_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/platform-input.c
        ${CMAKE_CURRENT_LIST_DIR}/platform-output.c
        ${CMAKE_CURRENT_LIST_DIR}/platform-bridge.c
        ${CMAKE_CURRENT_LIST_DIR}/platform-time.c
        ${CMAKE_CURRENT_LIST_DIR}/../../src/storage/storage-async.c
        )

set(PLATFORM_CONFIGURATION
        DIAG_STORAGE_ASYNC
        DIAG_STORAGE_TRACE
        DIAG_BRIDGE
        EXTERNAL_ISOTP
        PROTOCOL_DEBUG
        UDS_DEBUG
        PROJECT_NAME="${CMAKE_PROJECT_NAME}"
        )



