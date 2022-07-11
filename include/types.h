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


#endif //UDS_SERVER_TYPES_H
