//
// Created by tumap on 7/5/22.
//

#ifndef UDS_SERVER_STORAGE_H
#define UDS_SERVER_STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "diag/uds.h"
#ifdef STORAGE_CANBUS_ACCESS
#include "can-bus.h"
#endif

#ifdef DIAG_STORAGE_ASYNC
// implemented by FRAMEWORK
void diag_ecu_storage_query(uint16_t sequence_id);

// implemented by IMPLEMENTATION
void diag_ecu_storage_response(uint16_t sequence_id, unsigned length, uint8_t* content);
#else
// implemented by FRAMEWORK
eDiagStatus diag_ecu_storage_query(uint16_t sequence_id, unsigned* length, uint8_t* content);
#endif

// implemented by FRAMEWORK
eDiagStatus diag_ecu_storage_update(uint16_t sequence_id, unsigned length, const uint8_t* content);


#ifndef DIAG_STOTAGE_ASYNC
enum eStorageRecordAccess {
    STORAGE_ACCESS_HIDDEN,
    STORAGE_ACCESS_READ_ONLY,
    STORAGE_ACCESS_READ_WRITE,
    STORAGE_ACCESS_READ_INCREMENT,
};
typedef enum eStorageRecordAccess eStorageRecordAccess;

struct tStorageRecord {
    unsigned position: 16;
    unsigned length: 2;
    eStorageRecordAccess access: 2;
};
typedef struct tStorageRecord tStorageRecord;

// implemented by IMPLEMENTATION
extern const tStorageRecord* diag_storage_config_records;
extern const unsigned diag_storage_config_count;

#endif

#ifdef STORAGE_CANBUS_ACCESS
bool diag_storage_message_received(const tCANMessage* msg);
#endif

#endif //UDS_SERVER_STORAGE_H
