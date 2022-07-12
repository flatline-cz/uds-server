// Copyright
#include <stdbool.h>
#include "uds-common-responses.h"
#include "platform.h"
#include "framework.h"
#include "implementation.h"
#include "log.h"
#include "../fieldset/uds-fieldset.h"

/**
 * Service declarations (code & handler)
 */

#define UDS_SID_TESTER_PRESENT                  0x3e

static void handler_tester_present(const uint8_t *data, unsigned length);

#define UDS_SID_READ_DATA_BY_ID                 0x22

static void handler_read_by_id(const uint8_t *data, unsigned length);

#if UDS_INCLUDE_DTC == 1
#define UDS_SID_CLEAR_DTC                       0x14
#define UDS_SID_READ_DTC                        0x19
#endif


tServerContext serverContext;


void uds_server_reset() {
    // session is not active
    serverContext.session_active = false;
    serverContext.session_started = 0;
    serverContext.session_last_activity = 0;

    // reset field set
    uds_fieldset_reset();

}

void uds_server_request_received(const uint8_t* data, unsigned length) {
    LOG_INFO("UDSServer: Request received (%d bytes)", length);

    // update cache
    serverContext.now = uds_server_get_time();

    // check TESTER PRESENT
    if (length == 0) {
        // ignore
#ifdef UDS_DEBUG
        LOG_INFO("Empty UDS message, ignoring");
#endif
        return;
    }
    if (data[0] == UDS_SID_TESTER_PRESENT) {
        handler_tester_present(data, length);
        return;
    }

    // check other services
    if (!serverContext.session_active) {
#ifdef UDS_DEBUG
        LOG_INFO("No session active, ignoring");
#endif
        // FIXME: no session active
        uds_send_SNS(data);
        return;
    }

    switch (data[0]) {
        case UDS_SID_READ_DATA_BY_ID:
            handler_read_by_id(data, length);
            return;
#if UDS_INCLUDE_DTC == 1
        case UDS_SID_READ_DTC:
        case UDS_SID_CLEAR_DTC:
            return;
#endif
        default:
            uds_send_SNS(data);
            return;
    }
}

bool uds_server_idle() {
    // check session timeout
    if (!serverContext.session_active)
        return false;

    // update cache
    serverContext.now = uds_server_get_time();

    // FIXME: use constant for timeout
    if (serverContext.session_last_activity + 5000 <= serverContext.now) {
        // reset server
        uds_server_reset();
        return true;
    }

    // did nothing
    return false;
}

static void handler_tester_present(const uint8_t *data, unsigned length) {
#ifdef UDS_DEBUG
    LOG_INFO("==== TESTER PRESENT ====");
#endif
    // verify length
    if (length != 2) {
        uds_send_IMLOIF(data);
        return;
    }

    // session already active?
    if (!serverContext.session_active) {
        // activate a new session
        uds_server_reset();
        serverContext.session_active = true;
        serverContext.session_started = serverContext.now;
        serverContext.session_last_activity = serverContext.now;
    }

    // extend timeout
    serverContext.session_last_activity = serverContext.now;

    // send positive response
    static uint8_t response[2];
    response[0]=data[0] | 0x40;
    response[1]=0x00;
    uds_server_send_response(response, 2);
}

static void handler_read_by_id(const uint8_t* data, unsigned length) {

    // verify message length
    if (length < 3 || ((length - 1) % 2) != 0) {
        // SEND IMLOIF
        uds_send_IMLOIF(data);
        return;
    }
    if (length > 21) {
        // SEND RTL
        uds_send_RTL(data);
        return;
    }

    // build response
#define MAX_READ_DATA_RESPONSE_LENGTH       100
    static uint8_t response[MAX_READ_DATA_RESPONSE_LENGTH+10];  // FIXME
    response[0]=data[0] | 0x40;
    unsigned position = 1;
    int i;
    int postponed = 0;
    for (i = 1; i < length; i += 2) {
        int res;
        unsigned bytes=0;
        if (MAX_READ_DATA_RESPONSE_LENGTH - position < 3) {
            uds_send_RTL(data);
            return;
        }
        response[position] = data[i];
        response[position + 1] = data[i + 1];
        eDiagStatus status= diag_uds_get_field(
                (int) ((((unsigned) data[i]) << 8) | data[i + 1]),
                response+position+2,
                &bytes,
                MAX_READ_DATA_RESPONSE_LENGTH-position-2);
        switch(status) {
            case OUT_OF_SPACE:
                uds_send_RTL(data);
                return;
            case QUERIED:
                postponed=true;
                continue;
            case OK:
                break;
            default:
                uds_send_ROOR(data);
                return;
        }
        position += 2 + bytes;
    }

    // nothing found?
    if (position == 1) {
        if (!postponed) {
            // SEND ROOR
            uds_send_ROOR(data);
        }
        return;
    }

    // send response
    uds_server_send_response(response, position);
}

