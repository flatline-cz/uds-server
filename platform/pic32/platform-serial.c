//
// Created by tumap on 7/7/22.
//
#include "platform-serial.h"


void platform_serial_init();

bool platform_serial_handle();

void platform_serial_send(char* message, unsigned length);
