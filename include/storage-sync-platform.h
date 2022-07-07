//
// Created by tumap on 7/7/22.
//

#ifndef UDS_SERVER_STORAGE_SYNC_PLATFORM_H
#define UDS_SERVER_STORAGE_SYNC_PLATFORM_H

#include <stdint.h>
#include <stdbool.h>

#ifndef STORAGE_SIZE
#define STORAGE_SIZE            256
#endif

#define STORAGE_BITMAP_SIZE     (((STORAGE_SIZE)+7) >> 3)

extern uint8_t diag_storage_content[STORAGE_SIZE];
extern uint8_t diag_storage_bitmap[STORAGE_BITMAP_SIZE];
extern bool diag_storage_loaded;
extern bool diag_storage_changed;

#endif //UDS_SERVER_STORAGE_SYNC_PLATFORM_H
