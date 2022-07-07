// Copyright
#include <stdbool.h>
#include "uds-server.h"
#include "common-responses.h"
#include "log.h"

/**
 * Service declarations (code & handler)
 */

#define UDS_SID_TESTER_PRESENT                  0x3e

static void handler_tester_present(tUDSRecord *request);

#define UDS_SID_READ_DATA_BY_ID                 0x22

static void handler_read_by_id(tUDSRecord *request);

#if UDS_INCLUDE_DTC == 1
#define UDS_SID_CLEAR_DTC                       0x14
#define UDS_SID_READ_DTC                        0x19
#endif

static tUDSRecord response;


typedef struct {
    // time moment cache
    tTime now;

    // current session
    bool session_active;
    tTime session_started;
    tTime session_last_activity;
    unsigned session_channel;
} tServerContext;
static tServerContext serverContext;


void uds_server_reset() {
    // session is not active
    serverContext.session_active = false;
    serverContext.session_started = 0;
    serverContext.session_last_activity = 0;
}

void uds_server_handle_request(tUDSRecord *request) {
    // update cache
    serverContext.now = uds_server_get_time();

    // check TESTER PRESENT
    if (request->length == 0) {
        // ignore
#ifdef UDS_DEBUG
        LOG_INFO("Empty UDS message, ignoring");
#endif
        return;
    }
    if (request->data[0] == UDS_SID_TESTER_PRESENT) {
        handler_tester_present(request);
        return;
    }

    // check other services
    if (!serverContext.session_active) {
#ifdef UDS_DEBUG
        LOG_INFO("No session active, ignoring");
#endif
        // FIXME: no session active
        uds_send_SNS(request);
        return;
    }
    if (serverContext.session_channel != request->channel) {
#ifdef UDS_DEBUG
        LOG_INFO("Another session active, ignoring");
#endif
        // FIXME: another session active
        uds_send_SNS(request);
        return;
    }

    switch (request->data[0]) {
        case UDS_SID_READ_DATA_BY_ID:
            handler_read_by_id(request);
            return;
#if UDS_INCLUDE_DTC == 1
        case UDS_SID_READ_DTC:
        case UDS_SID_CLEAR_DTC:
            return;
#endif
        default:
            uds_send_SNS(request);
            return;
    }
}

bool uds_server_idle() {
    // check session timeout
    if (!serverContext.session_active)
        return false;

    // update cache
    serverContext.now = time_get();

    // FIXME: use constant for timeout
    if (serverContext.session_last_activity + 5000 <= serverContext.now) {
        // reset server
        uds_server_reset();
        return true;
    }

    // did nothing
    return false;
}

static void handler_tester_present(tUDSRecord *request) {
#ifdef UDS_DEBUG
    LOG_INFO("==== TESTER PRESENT ====");
#endif
    // verify length
    if (request->length != 2) {
        uds_send_IMLOIF(request);
        return;
    }

    // session already active?
    if (serverContext.session_active) {
        // active -> channel is the same?
        if (serverContext.session_channel != request->channel) {
            // another session active -> ignore
            return;
        }
    } else {
        // activate a new session
        uds_server_reset();
        serverContext.session_active = true;
        serverContext.session_started = serverContext.now;
        serverContext.session_last_activity = serverContext.now;
        serverContext.session_channel = request->channel;
    }

    // extend timeout
    serverContext.session_last_activity = serverContext.now;

    // send positive response
    response.channel = request->channel;
    response.data[0] = request->data[0] | 0x40;
    response.data[1] = 0x00;
    response.length = 2;
    uds_server_send_response(&response);
}

static void handler_read_by_id(tUDSRecord *request) {

    // verify message length
    register unsigned length = request->length;
    if (length < 3 || ((length - 1) % 2) != 0) {
        // SEND IMLOIF
        uds_send_IMLOIF(request);
        return;
    }
    if (length > 21) {
        // SEND RTL
        uds_send_RTL(request);
        return;
    }

    // build response
    response.channel = request->channel;
    response.data[0] = request->data[0] | 0x40;
    unsigned position = 1;
    int i;
    int postponed = 0;
    for (i = 1; i < length; i += 2) {
        int res;
        unsigned bits;
        if (UDS_MAX_RECORD_LENGTH - position < 3) {
            uds_send_RTL(request);
            return;
        }
        response.data[position] = request->data[i];
        response.data[position + 1] = request->data[i + 1];
        fieldset_get_value(
                (int) ((((unsigned) request->data[i]) << 8) | request->data[i + 1]),
                &res,
                response.data + position + 2,
                UDS_MAX_RECORD_LENGTH - position - 2,
                &bits,
                serverContext.now);
        switch (res) {
            case FIELDSET_SMALL_BUFFER:
                uds_send_RTL(request);
                return;
            case FIELDSET_QUERIED:
                postponed = 1;
                continue;
            case FIELDSET_OK:
                break;
            default:
                continue;
        }
        position += 2 + ((bits + 7) >> 3);
    }

    // nothing found?
    if (position == 1) {
        if (!postponed) {
            // SEND ROOR
            uds_send_ROOR(request);
        }
        return;
    }

    // send response
    response.length = position;
    uds_server_send_response(&response);
}

