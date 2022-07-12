cmake_minimum_required(VERSION 3.20)

list(APPEND UDS_SERVER_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/uds/uds-server.c
        ${CMAKE_CURRENT_LIST_DIR}/uds/uds-common-responses.c
        ${CMAKE_CURRENT_LIST_DIR}/uds/uds-processor.c
        ${CMAKE_CURRENT_LIST_DIR}/fieldset/uds-fieldset.c
        )