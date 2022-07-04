//
// Created by tumap on 7/4/22.
//

#include "diag/ecu.h"
#include "diag/uds.h"

#ifdef DIAG_STORAGE_ASYNC
void diag_ecu_storage_query(uint16_t sequenceId) {

}
#else
bool diag_ecu_storage_query(uint16_t sequenceId, unsigned* length, uint8_t* content) {
    return false;
}
#endif

eDiagStatus diag_uds_get_field_common(unsigned field_id, uint8_t *buffer, unsigned *position, unsigned max_length) {
    return UNKNOWN_FIELD;
}

void diag_uds_send_response_string(uint32_t field_id, unsigned length, const uint8_t* data) {

}

void diag_uds_send_response_number(uint32_t field_id, uint32_t value, unsigned bytes) {

}

void diag_ecu_update_field(uint16_t fieldId, uint32_t value) {

}


int main(int argc, char** argv) {

    tCANMessage msg;

    diag_ecu_message_received(&msg);

    unsigned pos;
    diag_uds_get_field(0, 0, &pos, 0);


    return 0;
}