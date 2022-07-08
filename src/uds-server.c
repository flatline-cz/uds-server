//
// Created by tumap on 7/4/22.
//
#ifdef STORAGE_TRACE
#include <stdio.h>
#endif
#include "uds-server.h"
#include "ecu.h"
#include "uds.h"
#include "log.h"
#ifndef EXTERNAL_ISOTP
#include "iso-tp.h"
#endif


#ifndef EXTERNAL_ISOTP
#define ISOTP_MAX_MESSAGE_LENGTH        1024
static tISOTPContext isotp_context;
static uint8_t isotp_rx_buffer[ISOTP_MAX_MESSAGE_LENGTH];
#endif

eDiagStatus diag_uds_get_field_common(unsigned field_id, uint8_t * buffer, unsigned *position, unsigned max_length) {
    return UNKNOWN_FIELD;
}

void diag_uds_send_response_string(uint32_t field_id, unsigned length, const uint8_t* const data) {

}

void diag_uds_send_response_number(uint32_t field_id, uint32_t value, unsigned bytes) {

}

void diag_ecu_update_field(uint16_t fieldId, uint32_t value) {

}

void uds_server_request_received(const uint8_t* data, unsigned length) {
    LOG_INFO("UDSServer: Request received (%d bytes)", length);

}


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
    isotp_init_context(&isotp_context);
#endif

}

void uds_server_message_received(const tCANMessage* msg) {
    // handle UDS stream
#ifndef EXTERNAL_ISOTP
    // FIXME: interface configurable
    if(msg->interface==3 && isotp_message_received(&isotp_context, msg))
        return;
#endif

    // TODO: pass to bridge


    // pass to implementation
//    diag_ecu_message_received(msg);
}


