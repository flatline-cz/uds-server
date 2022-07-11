//
// Created by tumap on 7/6/22.
//
#include <unistd.h>
#include <memory.h>
#include "buffer.h"
#include "protocol.h"
#include "platform.h"

static tWriteBuffer write_buffer = {
        .name="Output"
};

void platform_output_handle() {
    buffer_write_send(&write_buffer, STDOUT_FILENO);
}

void platform_output_init() {
    buffer_make_nonblocking(STDOUT_FILENO);
}


tCommand response_command;

bool can_bus_send_message(const tCANMessage* msg) {
    response_command.type=CMD_TYPE_CAN_MESSAGE;
    memcpy(&response_command.can_message, msg, sizeof(tCANMessage));
    protocol_write(&response_command, &write_buffer);
    return true;
}


#ifdef EXTERNAL_ISOTP
void uds_server_send_response(const uint8_t* data, unsigned length) {
    response_command.type=CMD_TYPE_UDS;
    response_command.udsRecord.channel=UDS_CHANNEL_OBD;
    response_command.udsRecord.length=length;
    memcpy(response_command.udsRecord.data, data, length);
    protocol_write(&response_command, &write_buffer);
}
#endif


#ifdef DIAG_STORAGE_ASYNC
void diag_ecu_storage_query(uint16_t sequence_id) {
    // TODO:
}

eDiagStatus diag_ecu_storage_update(uint16_t sequence_id, const uint8_t* content, unsigned length) {
    // TODO:
    return OK;
}
#endif