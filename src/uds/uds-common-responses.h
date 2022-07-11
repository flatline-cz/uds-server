// Copyright

#ifndef UDS_SERVER_UDS_COMMON_RESPONSES_H
#define UDS_SERVER_UDS_COMMON_RESPONSES_H

#include <stdint.h>

void uds_send_SNS(const uint8_t* request);
void uds_send_ROOR(const uint8_t* request);
void uds_send_IMLOIF(const uint8_t* request);
void uds_send_RTL(const uint8_t* request);

#endif //UDS_SERVER_UDS_COMMON_RESPONSES_H
