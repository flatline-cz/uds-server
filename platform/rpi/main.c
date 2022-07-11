//
// Created by tumap on 7/5/22.
//
#include "framework.h"
#include "platform-input-output.h"


int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
    platform_input_init();
    platform_output_init();

    uds_server_init();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        platform_input_handle();
        platform_output_handle();

        uds_server_handle();
    }
#pragma clang diagnostic pop

}
