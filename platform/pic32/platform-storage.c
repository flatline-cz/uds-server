//
// Created by tumap on 7/7/22.
//

#ifndef STORAGE_CANBUS_ACCESS
#error "Missing storage CAN-BUS access"
#endif

#ifdef DIAG_ASYNC_STORAGE
#define "Asynchronous storage access not supported"
#endif

#include <xc.h>
#include <string.h>
#include "storage.h"
#include "storage-sync-platform.h"
#include "platform-storage.h"
#include "log.h"



uint8_t diag_storage_content[STORAGE_SIZE];
uint8_t diag_storage_bitmap[STORAGE_BITMAP_SIZE];
bool diag_storage_loaded=false;
bool diag_storage_changed=false;

static void EEPROM_Initialize(void);
static void EEPROM_WriteExecute( bool waitForDone );
static bool EEPROM_WordRead(uint32_t addr, uint32_t *data);
static bool EEPROM_IsBusy(void);
typedef enum
{
    EEPROM_UNLOCK_KEY1 = 0xEDB7,
    EEPROM_UNLOCK_KEY2 = 0x1248
} EEPROM_UNLOCK_KEYS;
#define EEPROM_32BIT_BOUNDRY    0xFFC
typedef enum
{
    EEPROM_STATE_NOT_READY      = 0x0,  // Data EEPROM is not ready for access
    EEPROM_STATE_READY          = 0x1,  // Data EEPROM is ready for access
} EEPROM_READY_STATE;
typedef enum
{
    EEPROM_READ_WRITE_COMPLETED = 0x0,
    EEPROM_READ_WRITE_START     = 0x1,
} EEPROM_READ_WRITE_CTRL;
typedef enum
{
    EEPROM_DISABLE_PROGRAM      = 0x0,
    EEPROM_ENABLE_PROGRAM       = 0x1,
} EEPROM_WRITE_ENABLE;
typedef enum
{
    EEPROM_DISABLE              = 0x0,
    EEPROM_ENABLE               = 0x1,
} EEPROM_POWER_CTRL;
typedef enum
{
    EEPROM_WORD_READ_OPERATION      = 0x0,  // Word Read command (WREN bit must be clear)
    EEPROM_WORD_WRITE_OPERATION     = 0x1,  // Word Write command (WREN bit must be set)
    EEPROM_PAGE_ERASE_OPERATION     = 0x2,  // Data EEPROM memory Page Erase command (WREN bit must be set)
    EEPROM_BULK_ERASE_OPERATION     = 0x3,  // Data EEPROM memory Bulk Erase command (WREN bit must be set)
    EEPROM_CONFIG_WRITE_OPERATION   = 0x4,  // Configuration register Write command (WREN bit must be set)
    EEPROM_RESERVED_OPERATION       = 0x7,  // Reserved
} EEPROM_OPERATION_MODE;

#define EEPROM_WORDS (STORAGE_SIZE>>2)



void platform_storage_init() {
    // initialize EEPROM
    EEPROM_Initialize();
    
    // read EEPROM content
    int i, j;
    bool status;
    for (i = 0; i < EEPROM_WORDS; i++) {
        j = 0;
        do {
            status = EEPROM_WordRead(i << 2, ((uint32_t*)diag_storage_content) + i);
            j++;
        } while (!status && j < 3);
        if (j == 3) {
            diag_storage_content[0] = 0;
            break;
        }
    }
    
    // clear dirty map
    memset(diag_storage_bitmap, 0, STORAGE_BITMAP_SIZE);
    
    
    diag_storage_loaded=true;
    LOG_INFO("PlatformStorage: Content loaded from EEPROM");
}



bool platform_storage_handle() {
    // TODO write down in progress?
    
    
    // idle
    return false;
}

bool diag_storage_message_received(const tCANMessage* msg) {
    // not handled
    return false;
}


static void EEPROM_Initialize(void) {
    /* Before accessing the Data EEPROM, configure the number of Wait states */
    CFGCON2bits.EEWS = 2;
    volatile uint32_t* con=&EECON;

    *con = _EECON_ON_MASK;

    while(!EECONbits.RDY);
    EECONSET = _EECON_WREN_MASK; // Enable writing to the EEPROM


    EECONCLR=_EECON_CMD_MASK;
    EECONSET=EEPROM_CONFIG_WRITE_OPERATION<<_EECON_CMD_POSITION;

    EEADDR = 0x00; // Addr 0x00 = DEVEE0;
    EEDATA = DEVEE0;
    EEPROM_WriteExecute(true); // Execute write and wait for finish

    EEADDR = 0x04; // Addr 0x04 = DEVEE1;
    EEDATA = DEVEE1;
    EEPROM_WriteExecute(true); // Execute write and wait for finish

    EEADDR = 0x08; // Addr 0x08 = DEVEE2;
    EEDATA = DEVEE2;
    EEPROM_WriteExecute(true); // Execute write and wait for finish

    EEADDR = 0x0C; // Addr 0x0C = DEVEE3;
    EEDATA = DEVEE3;
    EEPROM_WriteExecute(true); // Execute write and wait for finish


    EECONCLR = _EECON_WREN_MASK; // Turn off writes.
}

static void EEPROM_WriteExecute( bool waitForDone )
{
    volatile uint32_t processorStatus;

    processorStatus = __builtin_disable_interrupts();

    EEKEY    = EEPROM_UNLOCK_KEY1;
    EEKEY    = EEPROM_UNLOCK_KEY2;
    EECONSET = _EECON_RW_MASK;

    __builtin_mtc0(12, 0, processorStatus);

    if ( waitForDone == true )
        while ( EECONbits.RW == EEPROM_READ_WRITE_START );
}

static bool EEPROM_WordRead(uint32_t addr, uint32_t *data) {
    bool result = false;

    if (EEPROM_IsBusy() == false) {
        EEADDR = addr & EEPROM_32BIT_BOUNDRY;
        EECONbits.CMD = EEPROM_WORD_READ_OPERATION;

        EECONCLR = _EECON_WREN_MASK;
        EECONSET = _EECON_RW_MASK;

        while (EECONbits.RW == EEPROM_READ_WRITE_START);
        *data = EEDATA;

        result = true;
    }

    return (result);
}

static bool EEPROM_IsBusy(void) {
    if (EECONbits.RW == EEPROM_READ_WRITE_COMPLETED)
        return false;

    return true;
}

