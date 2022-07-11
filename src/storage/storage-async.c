//
// Created by tumap on 7/11/22.
//
#include "framework.h"
#include "implementation.h"
#include "platform.h"

#ifndef DIAG_STORAGE_ASYNC
#error "Asynchronous implementation, synchronous requested"
#endif

void uds_server_storage_response(uint16_t sequence_id, const uint8_t* content, unsigned length) {
#ifdef DIAG_BRIDGE
    if(uds_server_bridge_storage_response(sequence_id, content, length))
        return;
#endif
    diag_ecu_storage_response(sequence_id, content, length);
}
