//
// Created by tumap on 7/10/22.
//

#ifndef UDS_SERVER_FRAMEWORK_H
#define UDS_SERVER_FRAMEWORK_H

#include "can-bus.h"
#include "types.h"

// implemented by FRAMEWORK
void diag_uds_reset();

// implemented by FRAMEWORK
eDiagStatus diag_uds_get_field_common(unsigned field_id,
                                      uint8_t *buffer, unsigned *position,
                                      unsigned max_length);

// implemented by FRAMEWORK
#ifdef DIAG_STORAGE_ASYNC
void diag_uds_send_response_string(uint32_t field_id, unsigned length, const uint8_t* data);
void diag_uds_send_response_number(uint32_t field_id, uint32_t value, unsigned bytes);
#endif

// implemented by FRAMEWORK
void diag_ecu_update_field(uint16_t fieldId, uint32_t value);

#ifdef DIAG_STORAGE_ASYNC
// implemented by FRAMEWORK
void uds_server_storage_response(uint16_t sequence_id, const uint8_t* content, unsigned length);
#else
// implemented by FRAMEWORK
eDiagStatus diag_ecu_storage_query(uint16_t sequence_id, const uint8_t* content, unsigned* length);
// implemented by FRAMEWORK
eDiagStatus diag_ecu_storage_update(uint16_t sequence_id, const uint8_t* content, unsigned length);
#endif



#ifdef STORAGE_CANBUS_ACCESS
// implemented by FRAMEWORK
bool diag_storage_message_received(const tCANMessage* msg);
#endif

// implemented by FRAMEWORK
void uds_server_init();

// implemented by FRAMEWORK
bool uds_server_handle();

// implemented by FRAMEWORK
void uds_server_message_received(const tCANMessage* msg);

// implemented by FRAMEWORK
void uds_server_request_received(const uint8_t* data, unsigned length);

#ifndef EXTERNAL_ISOTP
// implemented by FRAMEWORK
void uds_server_send_response(const uint8_t* data, unsigned length);
#endif


#endif //UDS_SERVER_FRAMEWORK_H
