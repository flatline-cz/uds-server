//
// Created by tumap on 7/10/22.
//

#ifndef UDS_SERVER_TYPES_H
#define UDS_SERVER_TYPES_H

#include "can-bus.h"

typedef uint32_t tTime;

enum eDiagStatus {
    OK,
    UNKNOWN_FIELD,
    NOT_AVAILABLE,
    QUERIED,
    OUT_OF_SPACE,
    INVALID_PARAMS,
    INCORRECT_CONDITIONS
};
typedef enum eDiagStatus eDiagStatus;

#ifndef DIAG_STORAGE_ASYNC
enum eStorageRecordAccess {
    STORAGE_ACCESS_HIDDEN,
    STORAGE_ACCESS_READ_ONLY,
    STORAGE_ACCESS_READ_WRITE,
    STORAGE_ACCESS_READ_INCREMENT,
};
typedef enum eStorageRecordAccess eStorageRecordAccess;

struct tStorageRecord {
    unsigned position: 16;
    unsigned length: 6;
    eStorageRecordAccess access: 2;
};
typedef struct tStorageRecord tStorageRecord;
#endif

#ifdef DIAG_BRIDGE
struct tCANMessageId {
    unsigned interface;
    uint32_t id;
    bool extended;
};
typedef struct tCANMessageId tCANMessageId;
#endif

struct tServerContext {
    // time moment cache
    tTime now;

    // current session
    bool session_active;
    tTime session_started;
    tTime session_last_activity;
};
typedef struct tServerContext tServerContext;

struct tFieldDescriptor {
    uint16_t field_id;
    bool special;
    unsigned bits;
    bool has_timeout;
    uint16_t timeout;
};
typedef struct tFieldDescriptor tFieldDescriptor;


#endif //UDS_SERVER_TYPES_H
