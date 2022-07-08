//
// Created by tumap on 7/8/22.
//

#ifndef UDS_SERVER_PLATFORM_TIMER_H
#define UDS_SERVER_PLATFORM_TIMER_H

#include <stdbool.h>
#include "uds-server.h"

void platform_timer_init();

bool platform_timer_handle();

extern tTime now;

#endif //UDS_SERVER_PLATFORM_TIMER_H
