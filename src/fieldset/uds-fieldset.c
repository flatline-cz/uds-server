//
// Created by tumap on 7/11/22.
//
#include "framework.h"
#include "implementation.h"
#include "log.h"
#include "dgi-constants.h"
#include "uds-fieldset.h"

struct tFieldValue {
    // configuration
    uint16_t field_id;
    bool has_timeout;
    uint16_t timeout;
    unsigned bits;
    bool enabled;

    // status
    tTime value_timeout;
    tTime last_updated;

    // value
    uint32_t value;
};
typedef struct tFieldValue tFieldValue;

extern tServerContext serverContext;
static tFieldValue field_values[DG_FieldsCount];

eDiagStatus diag_uds_get_field_common(unsigned field_id,
                                      uint8_t *buffer, unsigned *position,
                                      unsigned max_length) {
    if (field_id >= DG_FieldsCount)
        return UNKNOWN_FIELD;

    tFieldValue *field = field_values + field_id;

    if (!field->enabled)
        return UNKNOWN_FIELD;

    if (((field->bits + 7) >> 3) > max_length)
        return OUT_OF_SPACE;

    if(field->has_timeout &&
            (field->last_updated==0 || field->value_timeout<=serverContext.now))
        return UNKNOWN_FIELD;

    uint32_t value = field->value;
    value &= ~((((uint32_t) 1) << (field->bits + 1)) - 1);

    int bytes = (int) ((field->bits + 7) >> 3);
    *position = bytes;
    while (bytes >= 0) {
        buffer[bytes--] = value & 0xff;
        value >>= 8;
    }

    return OK;
}

void diag_ecu_update_field(uint16_t fieldId, uint32_t value) {
    LOG_INFO("FieldSet: %08X => field %04X", value, fieldId);
    if (fieldId >= DG_FieldsCount)
        return;
    tFieldValue *field = field_values + fieldId;
    if (field->enabled) {
        field->value = value;
        field->last_updated = serverContext.now;
        if (field->has_timeout)
            field->value_timeout = serverContext.now + field->timeout;
    }
}

void uds_fieldset_init() {
    unsigned i;
    for (i = 0; i < DG_FieldsCount; i++) {
        field_values[i].field_id = i;
        field_values[i].bits = diag_field_descriptor_list[i].bits;
        field_values[i].has_timeout = diag_field_descriptor_list[i].has_timeout;
        field_values[i].timeout = diag_field_descriptor_list[i].timeout;
        field_values[i].enabled = !diag_field_descriptor_list[i].special;
        field_values[i].last_updated = 0;
        field_values[i].value_timeout = 0;
    }
}

void uds_fieldset_reset() {
    unsigned i;
    for (i = 0; i < DG_FieldsCount; i++) {
        field_values[i].last_updated = 0;
        field_values[i].value_timeout = 0;
    }
}
