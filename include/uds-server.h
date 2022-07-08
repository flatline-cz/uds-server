//
// Created by tumap on 7/5/22.
//

#ifndef UDS_SERVER_UDS_SERVER_H
#define UDS_SERVER_UDS_SERVER_H

#include <stdint.h>
#include "can-bus.h"

// implemented by FRAMEWORK
void uds_server_init();

// implemented by FRAMEWORK
void uds_server_message_received(const tCANMessage* msg);

// implemented by PLATFORM
typedef uint32_t tTime;
tTime uds_server_get_time();

// implemented by PLATFORM
void uds_server_send_message(const tCANMessage* msg);

#ifdef EXTERNAL_ISOTP
// implemented by FRAMEWORK
void uds_server_request_received(const uint8_t* data, unsigned length);

// implemented by PLATFORM
void uds_server_send_response(const uint8_t* data, unsigned length);
#endif


#endif //UDS_SERVER_UDS_SERVER_H
