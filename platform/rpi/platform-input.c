//
// Created by tumap on 7/6/22.
//
#include <unistd.h>
#include "protocol.h"
#include "log.h"
#include "platform-input-output.h"
#include "framework.h"


static tCommand request_command;

void server_integration_version_response(uint16_t version);

static void read_processor(uint8_t *cmd, unsigned length) {
#ifdef BUFFER_DEBUG
    LOG_DEBUG("Processing %d incomming bytes", length);
#endif
    if (!protocol_parse(cmd, length, &request_command)) {
        // processing failed
#ifdef BUFFER_DEBUG
        LOG_INFO("Ignoring %d byte", length);
#endif
        return;
    }

#ifdef PROTOCOL_DEBUG
    protocol_dump(&request_command, "IN");
#endif

#ifdef EXTERNAL_ISOTP
    if (request_command.type == CMD_TYPE_UDS) {
        uds_server_request_received(
                request_command.udsRecord.data,
                request_command.udsRecord.length);
        return;
    }
#endif

    if(request_command.type==CMD_TYPE_CAN_MESSAGE) {
        uds_server_message_received(&request_command.can_message);
        return;
    }

    if(request_command.type==CMD_TYPE_STORAGE_DATA) {
        uds_server_storage_response(
                request_command.storageData.sequence_id,
                request_command.storageData.data,
                request_command.storageData.length
                );
        return;
    }

    if(request_command.type==CMD_TYPE_VERSION_RESPONSE) {
        server_integration_version_response(request_command.version);
        return;
    }

}

static tReadBuffer read_buffer;
static tHandle read_handle = STDIN_FILENO;

static tReadChannel read_channels[2] = {
        {
                .buffer=&read_buffer,
                .handle=&read_handle,
                .processor=read_processor,
                .failureHandler=NULL
        },
        {
                .buffer=NULL
        }
};

void platform_input_init(int handle) {
    read_handle=handle;
    buffer_make_nonblocking(*read_channels[0].handle);
}

void platform_input_handle() {
    buffer_process_read(read_channels);
}


