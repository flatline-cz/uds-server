// Copyright

#include "uds-common-responses.h"
#include "framework.h"
#include "platform.h"

#define EXCEPTION_SNS           0x11
#define EXCEPTION_SFNS          0x12
#define EXCEPTION_IMLOIF        0x13
#define EXCEPTION_RTL           0x14
#define EXCEPTION_CNC           0x22
#define EXCEPTION_RSE           0x24
#define EXCEPTION_ROOR          0x31
#define EXCEPTION_GPE           0x72

static inline void send(const uint8_t *request, uint8_t exception) {
    static uint8_t data[3];
    data[0]=0x7f;
    data[1]=request[0];
    data[2]=exception;
    uds_server_send_response(data, 3);
}

void uds_send_SNS(const uint8_t *request) {
    send(request, EXCEPTION_SNS);
}

void uds_send_SFNS(const uint8_t *request) {
    send(request, EXCEPTION_SFNS);
}

void uds_send_IMLOIF(const uint8_t *request) {
    send(request, EXCEPTION_IMLOIF);
}

void uds_send_RTL(const uint8_t *request) {
    send(request, EXCEPTION_RTL);
}

void uds_send_ROOR(const uint8_t *request) {
    send(request, EXCEPTION_ROOR);
}

