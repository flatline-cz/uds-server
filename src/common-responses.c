// Copyright

#include "common-responses.h"
#include "interface/tester-outbound.h"

#ifdef UDS_THREADED
#include <pthread.h>
#endif

static tUDSRecord response;

#ifdef UDS_THREADED
static void* response_lock;
#define LOCK
#define UNLOCK
#else
#define LOCK
#define UNLOCK
#endif

#define EXCEPTION_SNS           0x11
#define EXCEPTION_SFNS          0x12
#define EXCEPTION_IMLOIF        0x13
#define EXCEPTION_RTL           0x14
#define EXCEPTION_CNC           0x22
#define EXCEPTION_RSE           0x24
#define EXCEPTION_ROOR          0x31
#define EXCEPTION_GPE           0x72

static inline void send(tUDSRecord *request, uint8_t exception) {
    LOCK;
    response.data[0] = 0x7f;
    response.data[1] = request->data[0];
    response.data[2] = exception;
    response.length = 3;
    response.channel = request->channel;
    uds_server_send_response(&response);
    UNLOCK;
}

void uds_send_SNS(tUDSRecord *request) {
    send(request, EXCEPTION_SNS);
}

void uds_send_SFNS(tUDSRecord *request) {
    send(request, EXCEPTION_SFNS);
}

void uds_send_IMLOIF(tUDSRecord *request) {
    send(request, EXCEPTION_IMLOIF);
}

void uds_send_RTL(tUDSRecord *request) {
    send(request, EXCEPTION_RTL);
}

void uds_send_ROOR(tUDSRecord *request) {
    send(request, EXCEPTION_ROOR);
}

