//
// Created by tumap on 7/4/22.
//
#ifdef STORAGE_TRACE

#include <stdio.h>

#endif

#include "framework.h"
#include "implementation.h"
#include "platform.h"
#include "log.h"

#ifndef EXTERNAL_ISOTP
#include "iso-tp.h"
#endif

#include "dgi-constants.h"

bool uds_server_idle();

#ifndef EXTERNAL_ISOTP
#define ISOTP_MAX_MESSAGE_LENGTH        1024
static tISOTPContext isotp_context;
static uint8_t isotp_rx_buffer[ISOTP_MAX_MESSAGE_LENGTH];
#endif

eDiagStatus diag_uds_get_field_common(unsigned field_id, uint8_t *buffer, unsigned *position, unsigned max_length) {
    return UNKNOWN_FIELD;
}

#ifdef DIAG_STORAGE_ASYNC
void diag_uds_send_response_string(uint32_t field_id, unsigned length, const uint8_t* const data) {

}

void diag_uds_send_response_number(uint32_t field_id, uint32_t value, unsigned bytes) {

}
#endif

void diag_ecu_update_field(uint16_t fieldId, uint32_t value) {

}

#ifndef EXTERNAL_ISOTP
void uds_server_send_response(const uint8_t* data, unsigned length) {
    isotp_send_data(&isotp_context, data, length);
}
#endif


void uds_server_init() {
#ifndef EXTERNAL_ISOTP
    isotp_context.rx_buffer=isotp_rx_buffer;
    isotp_context.rx_buffer_size=ISOTP_MAX_MESSAGE_LENGTH;
    isotp_context.handler_data_received=uds_server_request_received;
    isotp_context.handler_get_time=uds_server_get_time;
    isotp_context.handler_send_message=can_bus_send_message;

    // FIXME: configurable
    isotp_context.channel=3;
    isotp_context.tx_id=0x7e8;
    isotp_context.tx_id_extended=false;
    isotp_context.rx_id_single=0x7df;
    isotp_context.rx_id_single_extended=false;
    isotp_context.rx_id_single_enabled=true;
    isotp_context.rx_id=0x7e0;
    isotp_context.tx_id_extended=false;
    isotp_context.tx_timeout=100;
    isotp_init_context(&isotp_context);
#endif

}

bool uds_server_handle() {
    bool didSomething = false;
#ifndef EXTERNAL_ISOTP
    didSomething|= isotp_handle(&isotp_context);
#endif

    didSomething |= uds_server_idle();

    return didSomething;
}

#ifdef DIAG_BRIDGE
static inline void process_bridge_message(const tCANMessage *msg) {
    unsigned i;
    for (i = 0; i < DG_BRIDGE_MESSAGE_LIST_COUNT; i++) {
        if (msg->interface == diag_bridge_message_list[i].interface
            && msg->id == diag_bridge_message_list[i].id
            && msg->extended == diag_bridge_message_list[i].extended) {
            // match -> pass message
            uds_server_bridge_send_message(msg);
            return;
        }
    }
}
#endif

void uds_server_message_received(const tCANMessage *msg) {
    // handle UDS stream
#ifndef EXTERNAL_ISOTP
    // FIXME: interface configurable
    if(msg->interface==3 && isotp_message_received(&isotp_context, msg))
        return;
#endif

#ifdef DIAG_BRIDGE
    // pass to bridge
    process_bridge_message(msg);
#endif


    // pass to implementation
//    diag_ecu_message_received(msg);
}


