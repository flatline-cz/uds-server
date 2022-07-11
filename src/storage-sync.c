//
// Created by tumap on 7/7/22.
//
#include <memory.h>
#include "platform.h"
#include "framework.h"
#include "implementation.h"

#ifdef DIAG_STORAGE_ASYNC
#error "Synchronous implementation, async requested"
#endif

#define STORAGE_MAGIC_WORD      ((uint32_t )0xfa50a5f)

static bool loading_checked = false;

static bool check_loading();

/**
 * Get value from storage
 * @param sequence_id
 * @param length
 * @param content
 * @return
 */
eDiagStatus diag_ecu_storage_query(uint16_t sequence_id, unsigned *length, uint8_t *content) {
    // verify the storage is ready
    if (!diag_storage_loaded || !loading_checked) {
        if (!check_loading()) {
            loading_checked = false;
            diag_storage_loaded = false;
            return INCORRECT_CONDITIONS;
        }
    }
    // get record pointer & check length
    if (sequence_id >= diag_storage_config_count) {
        return UNKNOWN_FIELD;
    }
    register const tStorageRecord *const descriptor = diag_storage_config_records + sequence_id;
    if (*length < descriptor->length) {
        return OUT_OF_SPACE;
    }

    // copy value
    memcpy(content, diag_storage_content + descriptor->position, descriptor->length);
    *length = descriptor->length;

    return OK;
}


eDiagStatus diag_ecu_storage_update(uint16_t sequence_id, unsigned length, const uint8_t *content) {
    if (!diag_storage_loaded || !loading_checked) {
        if (!check_loading()) {
            loading_checked = false;
            diag_storage_loaded = false;
            return INCORRECT_CONDITIONS;
        }
    }
    // get record pointer & check length
    if (sequence_id >= diag_storage_config_count) {
        return UNKNOWN_FIELD;
    }
    register const tStorageRecord *const descriptor = diag_storage_config_records + sequence_id;
    if (length != descriptor->length) {
        return INVALID_PARAMS;
    }

    // update content
    int i;
    for (i = 0; i < length; i++) {
        if (diag_storage_content[descriptor->position + i] == content[i])
            continue;
        diag_storage_content[descriptor->position + i] = content[i];
        register unsigned bitmap_idx = (descriptor->position + i) >> 3;
        register unsigned bitmap_mask = 1 << ((descriptor->position + i) & 7);
        if (diag_storage_bitmap[bitmap_idx] & bitmap_mask)
            continue;
        diag_storage_bitmap[bitmap_idx] |= bitmap_mask;
        diag_storage_changed = true;
    }

    return OK;
}

static bool check_loading() {
    if (!diag_storage_loaded)
        return false;

    // verify magic word
    loading_checked = true;
    if (diag_storage_content[0] != (uint8_t) (STORAGE_MAGIC_WORD >> 24) ||
        diag_storage_content[1] != (uint8_t) (STORAGE_MAGIC_WORD >> 16) ||
        diag_storage_content[2] != (uint8_t) (STORAGE_MAGIC_WORD >> 8) ||
        diag_storage_content[3] != (uint8_t) STORAGE_MAGIC_WORD)
        goto clean_bitmap;

    // verify structure



    clean_bitmap:
    {
        int i;
        diag_storage_content[0] = (uint8_t) (STORAGE_MAGIC_WORD >> 24);
        diag_storage_content[1] = (uint8_t) (STORAGE_MAGIC_WORD >> 16);
        diag_storage_content[2] = (uint8_t) (STORAGE_MAGIC_WORD >> 8);
        diag_storage_content[3] = (uint8_t) STORAGE_MAGIC_WORD;
        memset(diag_storage_content + 4, 0, STORAGE_SIZE - 4);
        memset(diag_storage_bitmap, 0xff, STORAGE_BITMAP_SIZE);
    }
    return true;
}


