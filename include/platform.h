//
// Created by tumap on 7/10/22.
//

#ifndef UDS_SERVER_PLATFORM_H
#define UDS_SERVER_PLATFORM_H

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

// implemented by PLATFORM
tTime uds_server_get_time();


#ifndef DIAG_STORAGE_ASYNC

#ifndef STORAGE_SIZE
#define STORAGE_SIZE            256
#endif

#define STORAGE_BITMAP_SIZE     (((STORAGE_SIZE)+7) >> 3)

extern uint8_t diag_storage_content[STORAGE_SIZE];
extern uint8_t diag_storage_bitmap[STORAGE_BITMAP_SIZE];
extern bool diag_storage_loaded;
extern bool diag_storage_changed;
#endif

#ifdef DIAG_STORAGE_ASYNC
void diag_ecu_storage_query(uint16_t sequence_id);
eDiagStatus diag_ecu_storage_update(uint16_t sequence_id, const uint8_t* content, unsigned length);
#endif

#ifdef EXTERNAL_ISOTP
// implemented by PLATFORM
void uds_server_send_response(const uint8_t* data, unsigned length);
#endif

#ifdef DIAG_BRIDGE
void uds_server_bridge_send_message(const tCANMessage* msg);
void uds_server_bridge_query_storage(uint16_t sequenceId);
bool uds_server_bridge_storage_response(uint16_t sequenceId, const uint8_t* data, unsigned length);
#endif

#endif //UDS_SERVER_PLATFORM_H
