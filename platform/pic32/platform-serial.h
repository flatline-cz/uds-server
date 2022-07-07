//
// Created by tumap on 7/7/22.
//

#ifndef UDS_SERVER_PLATFORM_SERIAL_H
#define UDS_SERVER_PLATFORM_SERIAL_H

#include <stdbool.h>

void platform_serial_init();

bool platform_serial_handle();

void platform_serial_send(char* message, unsigned length);

#endif //UDS_SERVER_PLATFORM_SERIAL_H
