//
// Created by tumap on 7/7/22.
//

#ifndef STORAGE_CANBUS_ACCESS
#error "Missing storage CAN-BUS access"
#endif

#ifdef DIAG_ASYNC_STORAGE
#define "Asynchronous storage access ntot supported"
#endif

#include "storage.h"
#include "storage-sync-platform.h"
#include "platform-storage.h"


uint8_t diag_storage_content[STORAGE_SIZE];
uint8_t diag_storage_bitmap[STORAGE_BITMAP_SIZE];
bool diag_storage_loaded=false;
bool diag_storage_changed=false;



bool diag_storage_message_received(const tCANMessage* msg) {
    // not handled
    return false;
}