cmake_minimum_required(VERSION 3.20)
project(uds-server C)
set(CMAKE_C_STANDARD 99)

# Library
include(common/CMakeLists.txt)

# Generated diagnostic implementation
include(impl/CMakeLists.txt)


set(UDS_SERVER_SOURCES
        )

set(STORAGE_SOURCES
        )

include(src/CMakeLists.txt)


include(platform/test/CMakeLists.txt)


add_executable(uds-server-test
        ${UDS_SERVER_SOURCES}
        ${STORAGE_SOURCES}
        ${PLATFORM_SOURCES}
        ${DASHBOARD_LIB_SOURCES}
        ${DIAGNOSTIC_IMPL_SOURCES}
        )

target_compile_definitions(uds-server-test PRIVATE
        ${PLATFORM_CONFIGURATION}
        )

target_include_directories(uds-server-test PRIVATE
        include
        ${DASHBOARD_LIB_INCLUDES}
        ${DIAGNOSTIC_IMPL_INCLUDES}
        )

#target_link_libraries(uds-server PRIVATE
#        pthread
#        m
#        )

add_custom_command(
        TARGET uds-server-test
        POST_BUILD
        COMMAND $<$<CONFIG:release>:${CMAKE_STRIP}>
        ARGS --strip-all $<TARGET_FILE:uds-server-test>
)