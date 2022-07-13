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

static tHandle write_handle;

void platform_output_handle() {
    buffer_write_send(&write_buffer, write_handle);
}

void platform_output_init(int handle) {
    write_handle=handle;
    buffer_make_nonblocking(write_handle);
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
    response_command.udsRecord.length=length;
    memcpy(response_command.udsRecord.data, data, length);
    protocol_write(&response_command, &write_buffer);
}
#endif


void diag_ecu_version_query() {
    response_command.type=CMD_TYPE_VERSION_QUERY;
    protocol_write(&response_command, &write_buffer);
}

#ifdef DIAG_STORAGE_ASYNC
void diag_ecu_storage_query(uint16_t sequence_id) {
    response_command.type=CMD_TYPE_STORAGE_QUERY;
    response_command.storageQuery=sequence_id;
    protocol_write(&response_command, &write_buffer);
}

eDiagStatus diag_ecu_storage_update(uint16_t sequence_id, const uint8_t* content, unsigned length) {
    response_command.type=CMD_TYPE_STORAGE_DATA;
    response_command.storageData.sequence_id=sequence_id;
    response_command.storageData.length=length;
    memcpy(response_command.storageData.data, content, length);
    protocol_write(&response_command, &write_buffer);
    return OK;
}
#endif