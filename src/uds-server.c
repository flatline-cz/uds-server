//
// Created by tumap on 7/4/22.
//
#ifdef STORAGE_TRACE
#include <stdio.h>
#endif
#include "uds-server.h"
#include "diag/ecu.h"
#include "diag/uds.h"

#ifdef DIAG_STORAGE_ASYNC
void diag_ecu_storage_query(uint16_t sequence_id) {
#ifdef STORAGE_TRACE
    fprintf(stderr, "Storage async query: %04X\n", sequence_id);
#endif
}
#else
bool diag_ecu_storage_query(uint16_t sequence_id, unsigned* length, uint8_t* content) {
#ifdef STORAGE_TRACE
    fprintf(stderr, "Storage async query: %04X\n", sequence_id);
#endif
}
#endif

void diag_ecu_storage_update(uint16_t sequence_id, unsigned length, const uint8_t* content) {
    fprintf(stderr, "Storage update: %04X:", sequence_id);
    for(int i=0;i<length;i++)
        fprintf(stderr, " %02X", content[i]);
    fprintf(stderr, "\n");
}

eDiagStatus diag_uds_get_field_common(unsigned field_id, uint8_t * buffer, unsigned *position, unsigned max_length) {
    return UNKNOWN_FIELD;
}

void diag_uds_send_response_string(uint32_t field_id, unsigned length, const uint8_t* const data) {

}

void diag_uds_send_response_number(uint32_t field_id, uint32_t value, unsigned bytes) {

}

void diag_ecu_update_field(uint16_t fieldId, uint32_t value) {

}

void diag_ecu_set_message(const tCANMessage* msg) {

}


// implemented by FRAMEWORK
void uds_server_init() {

}

// implemented by FRAMEWORK
void uds_server_message_received(const tCANMessage* msg) {

}


#ifdef EXTERNAL_ISOTP
// implemented by FRAMEWORK
void uds_server_request_received(const uint8_t* data, unsigned length) {

}

#endif