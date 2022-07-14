cmake_minimum_required(VERSION 3.20)

list(APPEND UDS_SERVER_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/uds/uds-server.c
        ${CMAKE_CURRENT_LIST_DIR}/src/uds/uds-common-responses.c
        ${CMAKE_CURRENT_LIST_DIR}/src/uds/uds-processor.c
        ${CMAKE_CURRENT_LIST_DIR}/src/fieldset/uds-fieldset.c
        )

list(APPEND UDS_SERVER_INCLUDES
        ${CMAKE_CURRENT_LIST_DIR}/include
        )
