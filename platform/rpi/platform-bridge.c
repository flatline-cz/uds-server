//
// Created by tumap on 7/11/22.
//
#include "platform.h"
#include "framework.h"
#include "log.h"

#ifndef DIAG_BRIDGE
#error "No diag bridge configured"
#endif

#define MAX_REQUESTED_SEQUENCE_IDS      8
static uint16_t requested_sequence_id[MAX_REQUESTED_SEQUENCE_IDS];
static unsigned requested_sequence_id_count = 0;

void uds_server_bridge_send_message(const tCANMessage *msg) {
    LOG_INFO("Bridge: Message forwarded");
}

void uds_server_bridge_query_storage(uint16_t sequenceId) {
#ifdef DIAG_STORAGE_ASYNC
    if (requested_sequence_id_count < MAX_REQUESTED_SEQUENCE_IDS) {
        requested_sequence_id[requested_sequence_id_count++] = sequenceId;
        diag_ecu_storage_query(sequenceId);
    }
#else
    static uint8_t buffer[64];
    unsigned length = 64;
    if (diag_ecu_storage_query(sequenceId, &length, buffer) == OK) {
        uds_server_bridge_storage_response(sequenceId, buffer, length);
    }
#endif
}

#ifdef DIAG_STORAGE_ASYNC
bool uds_server_bridge_storage_response(uint16_t sequenceId, const uint8_t* data, unsigned length) {

}
#endif
