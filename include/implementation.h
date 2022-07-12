//
// Created by tumap on 7/10/22.
//

#ifndef UDS_SERVER_IMPLEMENTATION_H
#define UDS_SERVER_IMPLEMENTATION_H

#include "framework.h"
#include "types.h"

// implemented by IMPLEMENTATION
eDiagStatus diag_uds_get_field(unsigned field_id, uint8_t *buffer, unsigned *position, unsigned max_length);

// implemented by IMPLEMENTATION
eDiagStatus diag_uds_update_field(unsigned field_id, const uint8_t *buffer, unsigned* length);

// implemented by IMPLEMENTATION
eDiagStatus dsg_io_control(unsigned field_id, bool override, const uint8_t *buffer, unsigned* length);

// implemented by IMPLEMENTATION
void diag_ecu_message_received(const tCANMessage* msg);

#ifdef DIAG_STORAGE_ASYNC
// implemented by IMPLEMENTATION
void diag_ecu_storage_response(uint16_t sequence_id, const uint8_t* content, unsigned length);
#endif

#ifndef DIAG_STORAGE_ASYNC
// implemented by IMPLEMENTATION
extern const tStorageRecord diag_storage_config_records[];
extern const unsigned diag_storage_config_count;
#endif

#ifdef DIAG_BRIDGE
extern const tCANMessageId diag_bridge_message_list[];
#endif

extern const tFieldDescriptor  diag_field_descriptor_list[];

#endif //UDS_SERVER_IMPLEMENTATION_H
