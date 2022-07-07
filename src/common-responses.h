// Copyright

#ifndef UDS_SERVER_COMMON_RESPONSES_H
#define UDS_SERVER_COMMON_RESPONSES_H

#include <protocol.h>

void uds_send_SNS(tUDSRecord* request);
void uds_send_ROOR(tUDSRecord* request);
void uds_send_IMLOIF(tUDSRecord* request);
void uds_send_RTL(tUDSRecord* request);

#endif //UDS_SERVER_COMMON_RESPONSES_H
