//
// Created by tumap on 7/10/22.
//

#ifndef UDS_SERVER_PLATFORM_INPUT_OUTPUT_H
#define UDS_SERVER_PLATFORM_H

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

// implemented by PLATFORM
tTime uds_server_get_time();


// implemented by PLATFORM
void uds_server_send_message(const tCANMessage* msg);


#ifndef DIAG_STORAGE_ASYNC

#ifndef STORAGE_SIZE
#define STORAGE_SIZE            256
#endif

#define STORAGE_BITMAP_SIZE     (((STORAGE_SIZE)+7) >> 3)

extern uint8_t diag_storage_content[STORAGE_SIZE];
extern uint8_t diag_storage_bitmap[STORAGE_BITMAP_SIZE];
extern bool diag_storage_loaded;
extern bool diag_storage_changed;

#endif

#ifdef EXTERNAL_ISOTP
// implemented by PLATFORM
void uds_server_send_response(const uint8_t* data, unsigned length);
#endif

#endif //UDS_SERVER_PLATFORM_INPUT_OUTPUT_H
