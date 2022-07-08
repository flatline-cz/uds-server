//
// Created by tumap on 7/7/22.
//
#include <xc.h>
#include <sys/attribs.h>
#include <sys/kmem.h>
#include "can-bus.h"
#include "platform-canbus.h"
#include "log.h"
#include "uds-server.h"

#define CAN_RX_BUFFER_LENGTH        64

typedef struct {
    uint32_t w1;
    uint32_t w2;
    uint8_t data[8];
} tCANHWRecord;

#define CANBUS_FAILURE_SYSTEM_ERROR             0x01
#define CANBUS_FAILURE_BUS_ERROR                0x02
#define CANBUS_FAILURE_INVALID_MESSAGE_ERROR    0x04

typedef struct {
    // rx buffers
    tCANHWRecord rx_buffer[CAN_RX_BUFFER_LENGTH];
    unsigned rx_position;
    unsigned rx_length;
    bool rx_enabled;
    uint32_t failures;
} tCANInterface;

static tCANInterface canbus_interface[4];


typedef enum {
    CAN_NORMAL = 0, CAN_INIT_MODE4, CAN_INIT_TARGET_MODE, CAN_NOTHING
} eCANState;
static eCANState states[4] = {CAN_NOTHING, CAN_NOTHING, CAN_NOTHING, CAN_NOTHING};

static volatile uint32_t *const CFDxCON[4] = {&CFD1CON, &CFD2CON, &CFD3CON, &CFD4CON};
static volatile uint32_t *const CFDxCONSET[4] = {&CFD1CONSET, &CFD2CONSET, &CFD3CONSET, &CFD4CONSET};
static volatile uint32_t *const CFDxCONCLR[4] = {&CFD1CONCLR, &CFD2CONCLR, &CFD3CONCLR, &CFD4CONCLR};
static volatile uint32_t *const CFDxDBTCFG[4] = {&CFD1DBTCFG, &CFD2DBTCFG, &CFD3DBTCFG, &CFD4DBTCFG};
static volatile uint32_t *const CFDxNBTCFG[4] = {&CFD1NBTCFG, &CFD2NBTCFG, &CFD3NBTCFG, &CFD4NBTCFG};
static volatile uint32_t *const CFDxINT[4] = {&CFD1INT, &CFD2INT, &CFD3INT, &CFD4INT};
static volatile uint32_t *const CFDxFIFOBA[4] = {&CFD1FIFOBA, &CFD2FIFOBA, &CFD3FIFOBA, &CFD4FIFOBA};
static volatile uint32_t *const CFDxTXQCON[4] = {&CFD1TXQCON, &CFD2TXQCON, &CFD3TXQCON, &CFD4TXQCON};
static volatile uint32_t *const CFDxTXQCONSET[4] = {&CFD1TXQCONSET, &CFD2TXQCONSET, &CFD3TXQCONSET, &CFD4TXQCONSET};
static volatile uint32_t *const CFDxTXQUA[4] = {&CFD1TXQUA, &CFD2TXQUA, &CFD3TXQUA, &CFD4TXQUA};
static volatile uint32_t *const CFDxTXQSTA[4] = {&CFD1TXQSTA, &CFD2TXQSTA, &CFD3TXQSTA, &CFD4TXQSTA};
static volatile uint32_t *const CFDxFIFOCON1[4] = {&CFD1FIFOCON1, &CFD2FIFOCON1, &CFD3FIFOCON1, &CFD4FIFOCON1};
static volatile uint32_t *const CFDxFLTOBJ0[4] = {&CFD1FLTOBJ0, &CFD2FLTOBJ0, &CFD3FLTOBJ0, &CFD4FLTOBJ0};
static volatile uint32_t *const CFDxMASK0[4] = {&CFD1MASK0, &CFD2MASK0, &CFD3MASK0, &CFD4MASK0};
static volatile uint32_t *const CFDxFLTCON0[4] = {&CFD1FLTCON0, &CFD2FLTCON0, &CFD3FLTCON0, &CFD4FLTCON0};
static volatile uint32_t *const CFDxFLTCON0SET[4] = {&CFD1FLTCON0SET, &CFD2FLTCON0SET, &CFD3FLTCON0SET,
                                                     &CFD4FLTCON0SET};

#define CANFD_MESSAGE_RAM_CONFIG_SIZE 1024
static uint8_t __attribute__((coherent, aligned(16))) can_message_buffer1[CANFD_MESSAGE_RAM_CONFIG_SIZE];
static uint8_t __attribute__((coherent, aligned(16))) can_message_buffer2[CANFD_MESSAGE_RAM_CONFIG_SIZE];
static uint8_t __attribute__((coherent, aligned(16))) can_message_buffer3[CANFD_MESSAGE_RAM_CONFIG_SIZE];
static uint8_t __attribute__((coherent, aligned(16))) can_message_buffer4[CANFD_MESSAGE_RAM_CONFIG_SIZE];

static uint8_t *message_buffers[4] = {can_message_buffer1, can_message_buffer2, can_message_buffer3,
                                      can_message_buffer4};


#define SPEED_500_DBTCFG ((1 << _CFD1DBTCFG_BRP_POSITION) & _CFD1DBTCFG_BRP_MASK) \
               | ((31 << _CFD1DBTCFG_TSEG1_POSITION) & _CFD1DBTCFG_TSEG1_MASK) \
               | ((6 << _CFD1DBTCFG_TSEG2_POSITION) & _CFD1DBTCFG_TSEG2_MASK) \
               | ((6 << _CFD1DBTCFG_SJW_POSITION) & _CFD1DBTCFG_SJW_MASK)

//#define SPEED_500_NBTCFG ((0 << _CFD1NBTCFG_BRP_POSITION) & _CFD1NBTCFG_BRP_MASK) \
//               | ((77 << _CFD1NBTCFG_TSEG1_POSITION) & _CFD1NBTCFG_TSEG1_MASK) \
//               | ((0 << _CFD1NBTCFG_TSEG2_POSITION) & _CFD1NBTCFG_TSEG2_MASK) \
//               | ((0 << _CFD1NBTCFG_SJW_POSITION) & _CFD1NBTCFG_SJW_MASK)

#define SPEED_500_NBTCFG ((0 << _CFD1NBTCFG_BRP_POSITION) & _CFD1NBTCFG_BRP_MASK) \
               | ((62 << _CFD1NBTCFG_TSEG1_POSITION) & _CFD1NBTCFG_TSEG1_MASK) \
               | ((15 << _CFD1NBTCFG_TSEG2_POSITION) & _CFD1NBTCFG_TSEG2_MASK) \
               | ((15 << _CFD1NBTCFG_SJW_POSITION) & _CFD1NBTCFG_SJW_MASK)

#define SPEED_250_DBTCFG ((3 << _CFD2DBTCFG_BRP_POSITION) & _CFD2DBTCFG_BRP_MASK) \
               | ((31 << _CFD2DBTCFG_TSEG1_POSITION) & _CFD2DBTCFG_TSEG1_MASK) \
               | ((6 << _CFD2DBTCFG_TSEG2_POSITION) & _CFD2DBTCFG_TSEG2_MASK) \
               | ((6 << _CFD2DBTCFG_SJW_POSITION) & _CFD2DBTCFG_SJW_MASK)

#define SPEED_250_NBTCFG ((0 << _CFD2NBTCFG_BRP_POSITION) & _CFD2NBTCFG_BRP_MASK) \
               | ((127 << _CFD2NBTCFG_TSEG1_POSITION) & _CFD2NBTCFG_TSEG1_MASK) \
               | ((30 << _CFD2NBTCFG_TSEG2_POSITION) & _CFD2NBTCFG_TSEG2_MASK) \
               | ((30 << _CFD2NBTCFG_SJW_POSITION) & _CFD2NBTCFG_SJW_MASK)

#define TX_QUEUE_CFG (((32 - 1) << _CFD3TXQCON_FSIZE_POSITION) & _CFD3TXQCON_FSIZE_MASK) \
               | ((0x0 << _CFD3TXQCON_PLSIZE_POSITION) & _CFD3TXQCON_PLSIZE_MASK) \
               | ((0x0 << _CFD3TXQCON_TXPRI_POSITION) & _CFD3TXQCON_TXPRI_MASK) \
               | ((0x1 << _CFD3TXQCON_TXAT_POSITION) & _CFD3TXQCON_TXAT_MASK)

#define RX_QUEUE_CFG (((32 - 1) << _CFD3FIFOCON1_FSIZE_POSITION) & _CFD3FIFOCON1_FSIZE_MASK) \
                | ((0x0 << _CFD3FIFOCON1_PLSIZE_POSITION) & _CFD3FIFOCON1_PLSIZE_MASK) \
                | ((0x1 << _CFD2FIFOCON1_TFNRFNIE_POSITION) & _CFD3FIFOCON1_TFNRFNIE_MASK)

typedef struct {
    /* CANFD Tx message - SID[10:0] and EID[28:11] */
    uint32_t t0;

    /* CANFD Tx message - DLC[3:0], IDE[4], RTR[5], BRS[6], FDF[7]
                          ESI[8] and SEQ[31:9] */
    uint32_t t1;

    /* CANFD Tx message - Transmit Buffer Data Bytes */
    uint8_t data[];
} CANFD_TX_MSG_OBJECT;

#define CANFD_MSG_SID_MASK            0x7FF
#define CANFD_MSG_EID_MASK            0x1FFFFFFF
#define CANFD_MSG_DLC_MASK            0x0000000F
#define CANFD_MSG_IDE_MASK            0x00000010
#define CANFD_MSG_RTR_MASK            0x00000020
#define CANFD_MSG_BRS_MASK            0x00000040
#define CANFD_MSG_FDF_MASK            0x00000080
#define CANFD_MSG_SEQ_MASK            0xFFFFFE00
#define CANFD_MSG_TX_EXT_SID_MASK     0x1FFC0000
#define CANFD_MSG_TX_EXT_EID_MASK     0x0003FFFF
#define CANFD_MSG_RX_EXT_SID_MASK     0x000007FF
#define CANFD_MSG_RX_EXT_EID_MASK     0x1FFFF800
#define CANFD_MSG_FLT_EXT_SID_MASK    0x1FFC0000
#define CANFD_MSG_FLT_EXT_EID_MASK    0x0003FFFF

static uint32_t interrupt_masks[4] = {_IFS5_CAN1IF_MASK, _IFS5_CAN2IF_MASK, _IFS5_CAN3IF_MASK, _IFS5_CAN4IF_MASK};

static void receive_message(int channel);

static unsigned get_raw_mode(const tCANConfig *config) {
//    return 6;
    if (config->enabled) {
        if (config->receive_only)
            return 7;
        else
            return 6;
    } else {
        return 4;
    }
}

void platform_canbus_init() {
    // interrupts
    IPC41bits.CAN1IP = 2;
    IPC41bits.CAN1IS = 0;
    
    IPC42bits.CAN2IP = 2;
    IPC42bits.CAN2IS = 0;
    
    IPC46bits.CAN3IP = 2;
    IPC46bits.CAN3IS = 0;
    
    IPC47bits.CAN4IP = 2;
    IPC47bits.CAN4IS = 0;
    
    // port initialization
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB9 = 0;
    TRISBbits.TRISB9 = 0;
    ANSELCbits.ANSC0 = 0;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSC1 = 0;
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC6 = 0;
    
    // PPS initialization
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    C1RXR = 6;
    C2RXR = 4;
    C3RXR = 5;
    C4RXR = 2;
    
    RPC0R = 12; // C1TX
    RPB9R = 12; // C2TX
    RPC6R = 12; // C3TX
    RPB1R = 12; // C4TX

    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;
    
    // walk through all 4 channels
    int channel;
    for (channel = 0; channel < 4; channel++) {
        // interface enabled?
        if ((*CFDxCON[channel] & _CFD1CON_ON_MASK) == 0) {
            *CFDxCONSET[channel] = _CFD1CON_ON_MASK | _CFD1CON_CLKSEL0_MASK;
        }

        // lock rx buffers
        __builtin_disable_interrupts();
        canbus_interface[channel].rx_enabled = false;
        canbus_interface[channel].rx_length = 0;
        canbus_interface[channel].rx_position = 0;
        canbus_interface[channel].failures = 0;
        __builtin_enable_interrupts();


        // mode matches?
        unsigned mode = ((*CFDxCON[channel]) & _CFD1CON_OPMOD_MASK) >> _CFD1CON_OPMOD_POSITION;
        if (get_raw_mode(diag_canbus_config + channel) == mode) {
            // ok
            states[channel] = CAN_NORMAL;
            canbus_interface[channel].rx_enabled = true;
            LOG_INFO("PlatformCAN: Channel #%d initialized", channel);
            continue;
        }

        // reset channel
        states[channel] = CAN_INIT_MODE4;
    }

}


bool platform_canbus_handle() {
    // walk through all 4 channels
    int channel;
    for (channel = 0; channel < 4; channel++) {

        unsigned mode;

        // depends on state
        switch (states[channel]) {
            case CAN_NOTHING:
                break;
            case CAN_INIT_MODE4:
                //  MODE4 requested?
                mode = ((*CFDxCON[channel]) & _CFD1CON_REQOP_MASK) >> _CFD1CON_REQOP_POSITION;
                if (mode != 4) {
                    // request MODE4
                    *CFDxCON[channel] = ((*CFDxCON[channel]) & ~_CFD1CON_REQOP_MASK) | (4 << _CFD1CON_REQOP_POSITION);
                    break;
                }
                // MODE4 active
                mode = ((*CFDxCON[channel]) & _CFD1CON_OPMOD_MASK) >> _CFD1CON_OPMOD_POSITION;
                if (mode != 4)
                    break;

                // channel not active?
                if (diag_canbus_config[channel].enabled == false) {
                    states[channel] = CAN_INIT_TARGET_MODE;
                    break;
                }

                // configure interface (bit rate)
                if (diag_canbus_config[channel].speed == CANBUS_250K) {
                    (*CFDxDBTCFG[channel]) = SPEED_250_DBTCFG;
                    (*CFDxNBTCFG[channel]) = SPEED_250_NBTCFG;
                } else {
                    (*CFDxDBTCFG[channel]) = SPEED_500_DBTCFG;
                    (*CFDxNBTCFG[channel]) = SPEED_500_NBTCFG;
                }

                // set buffer address
                (*CFDxFIFOBA[channel]) = (uint32_t) KVA_TO_PA(message_buffers[channel]);

                // no transmit event FIFO
                (*CFDxCONCLR[channel]) = _CFD1CON_STEF_MASK;

                // TX queue configuration
                (*CFDxTXQCON[channel]) = TX_QUEUE_CFG;
                (*CFDxCONSET[channel]) = _CFD1CON_TXQEN_MASK;
                (*CFDxCONSET[channel]) = _CFD1CON_RTXAT_MASK;

                // RX queue configuration
                (*CFDxFIFOCON1[channel]) = RX_QUEUE_CFG;

                // set filters
                unsigned index;
                for (index = 0; index < 8; index++)
                    (*(CFDxFLTCON0[channel] + index * 16)) = 0;
                
                for (index = 0; diag_canbus_config[channel].filters[index].id != 0; index++) {
                    if(diag_canbus_config[channel].filters[index].extended) {
                        (*(CFDxFLTOBJ0[channel] + index * 8)) = 
                                ((diag_canbus_config[channel].filters[index].id >> 18) & 0x000007ff) |
                                ((diag_canbus_config[channel].filters[index].id & 0x0003ffff) << 11) |
                                0x40000000;
                        (*(CFDxMASK0[channel] + index * 8)) = 
                                ((diag_canbus_config[channel].filters[index].mask >> 18) & 0x000007ff) |
                                ((diag_canbus_config[channel].filters[index].mask & 0x0003ffff) << 11) |
                                0x40000000;
                        
                    } else {
                        (*(CFDxFLTOBJ0[channel] + index * 8)) = diag_canbus_config[channel].filters[index].id;
                        (*(CFDxMASK0[channel] + index * 8)) = diag_canbus_config[channel].filters[index].mask | 0x40000000;
                    }
                    (*(CFDxFLTCON0SET[channel]+(index >> 2)*4)) = 0x81U << ((index & 0x3)*8);
                }

                // set up interrupts
                (*(CFDxINT[channel])) =
                        _CFD1INT_RXIE_MASK | _CFD1INT_IVMIE_MASK | _CFD1INT_CERRIE_MASK | _CFD1INT_SERRIE_MASK;
                IFS5CLR = interrupt_masks[channel];
                IEC5SET = interrupt_masks[channel];

                // next state
                states[channel] = CAN_INIT_TARGET_MODE;
                break;

            case CAN_INIT_TARGET_MODE:
                canbus_interface[channel].failures = 0;
                // target mode requested?
                mode = ((*CFDxCON[channel]) & _CFD1CON_REQOP_MASK) >> _CFD1CON_REQOP_POSITION;
                unsigned target_mode = get_raw_mode(&diag_canbus_config[channel]);
                if (mode != target_mode) {
                    // request target mode
                    *CFDxCON[channel] =
                            ((*CFDxCON[channel]) & ~_CFD1CON_REQOP_MASK) | (target_mode << _CFD1CON_REQOP_POSITION);
                    break;
                }
                // MODE4 active
                mode = ((*CFDxCON[channel]) & _CFD1CON_OPMOD_MASK) >> _CFD1CON_OPMOD_POSITION;
                if (mode != target_mode)
                    break;

                // OK -> normal processing
                states[channel] = CAN_NORMAL;
                LOG_INFO("PlatformCAN: Channel #%d initialized", channel);
                break;

            case CAN_NORMAL:
                receive_message(channel);
                break;
        }
    }

    return true;
}


static void receive_message(int channel) {
    // message received?
    int pos = -1;
    __builtin_disable_interrupts();
    if (canbus_interface[channel].rx_length)
        pos = canbus_interface[channel].rx_position;
    __builtin_enable_interrupts();
    if (pos == -1)
        return;

    // extract message
    tCANMessage msg;
    bool valid=false;
    msg.interface=channel;
    tCANHWRecord* src = (tCANHWRecord*) (canbus_interface[channel].rx_buffer + pos);
    if (src->w2 & CANFD_MSG_IDE_MASK) {
        msg.id = (((src->w1 & CANFD_MSG_RX_EXT_SID_MASK) << 18) | ((src->w1 & CANFD_MSG_RX_EXT_EID_MASK) >> 11)) & CANFD_MSG_EID_MASK;
        msg.id |= 0x80000000;
    } else {
        msg.id = src->w1 & CANFD_MSG_SID_MASK;
    }
    if (src->w2 & CANFD_MSG_RTR_MASK && (src->w2 & CANFD_MSG_FDF_MASK) == 0)
        goto release_message;
    msg.dlc = src->w2&CANFD_MSG_DLC_MASK;
    if (msg.dlc > 8)
        goto release_message;
    for (pos = 0; pos < msg.dlc; pos++)
        msg.data[pos] = src->data[pos];

    valid=true;

release_message:
    // update context
    __builtin_disable_interrupts();
    if (canbus_interface[channel].rx_length > 0) {
        canbus_interface[channel].rx_position = (canbus_interface[channel].rx_position + 1)&(CAN_RX_BUFFER_LENGTH - 1);
        canbus_interface[channel].rx_length--;
    } else {
        canbus_interface[channel].rx_length = 0;
        canbus_interface[channel].rx_position = 0;
    }
    __builtin_enable_interrupts();
    
    if(valid) {
        LOG_INFO("PlatformCAN: Message received on channel #%d", channel);
        uds_server_message_received(&msg);
    }

}


bool can_bus_send_message(const tCANMessage *msg) {
    return false;
}


#define CANFD_MSG_SID_MASK            0x7FF
#define CANFD_MSG_EID_MASK            0x1FFFFFFF
#define CANFD_MSG_DLC_MASK            0x0000000F
#define CANFD_MSG_IDE_MASK            0x00000010
#define CANFD_MSG_RTR_MASK            0x00000020
#define CANFD_MSG_BRS_MASK            0x00000040
#define CANFD_MSG_FDF_MASK            0x00000080
#define CANFD_MSG_SEQ_MASK            0xFFFFFE00
#define CANFD_MSG_TX_EXT_SID_MASK     0x1FFC0000
#define CANFD_MSG_TX_EXT_EID_MASK     0x0003FFFF
#define CANFD_MSG_RX_EXT_SID_MASK     0x000007FF
#define CANFD_MSG_RX_EXT_EID_MASK     0x1FFFF800
#define CANFD_MSG_FLT_EXT_SID_MASK    0x1FFC0000
#define CANFD_MSG_FLT_EXT_EID_MASK    0x0003FFFF

void __ISR(_CAN1_VECTOR, ipl2SRS)CAN1_Handler(void) {
    IFS5CLR = _IFS5_CAN1IF_MASK;
    // failure
    if (CFD1INT & _CFD1INT_SERRIF_MASK) {
        canbus_interface[0].failures |= CANBUS_FAILURE_SYSTEM_ERROR;
        CFD1INTCLR = _CFD1INT_SERRIF_MASK;
    }
    if (CFD1INT & _CFD1INT_CERRIF_MASK) {
        canbus_interface[0].failures |= CANBUS_FAILURE_BUS_ERROR;
        CFD1INTCLR = _CFD1INT_CERRIF_MASK;
    }
    if (CFD1INT & _CFD1INT_IVMIF_MASK) {
        canbus_interface[0].failures |= CANBUS_FAILURE_INVALID_MESSAGE_ERROR;
        CFD1INTCLR = _CFD1INT_IVMIF_MASK;
    }

    // message received?
    if (CFD1INT & _CFD1INT_RXIF_MASK) {
        // clear flag
        CFD1INTCLR = _CFD1INT_RXIF_MASK;

        // get FIFO number
        uint8_t fifoNum = (uint8_t) CFD1VEC & _CFD1VEC_ICODE_MASK;
        if (fifoNum != 1)
            return;


        // copy data
        if (canbus_interface[0].rx_length < CAN_RX_BUFFER_LENGTH) {
            uint32_t *src = (uint32_t *) PA_TO_KVA1(*(volatile uint32_t *) (&CFD1FIFOUA1));
            unsigned pos =
                    (canbus_interface[0].rx_position + canbus_interface[0].rx_length) & (CAN_RX_BUFFER_LENGTH - 1);
            uint32_t *dst = (uint32_t *) &canbus_interface[0].rx_buffer[pos].w1;
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *dst = *src;
            canbus_interface[0].rx_length++;
        }

        /* Message processing is done, update the message buffer pointer. */
        CFD1FIFOCON1SET = _CFD1FIFOCON1_UINC_MASK;
    }
}

void __ISR(_CAN2_VECTOR, ipl2SRS)CAN2_Handler(void) {
    IFS5CLR = _IFS5_CAN2IF_MASK;
    // failure
    if (CFD2INT & _CFD2INT_SERRIF_MASK) {
        canbus_interface[1].failures |= CANBUS_FAILURE_SYSTEM_ERROR;
        CFD2INTCLR = _CFD2INT_SERRIF_MASK;
    }
    if (CFD2INT & _CFD2INT_CERRIF_MASK) {
        canbus_interface[1].failures |= CANBUS_FAILURE_BUS_ERROR;
        CFD2INTCLR = _CFD2INT_CERRIF_MASK;
    }
    if (CFD2INT & _CFD2INT_IVMIF_MASK) {
        canbus_interface[1].failures |= CANBUS_FAILURE_INVALID_MESSAGE_ERROR;
        CFD2INTCLR = _CFD2INT_IVMIF_MASK;
    }

    // message received?
    if (CFD2INT & _CFD2INT_RXIF_MASK) {
        // clear flag
        CFD2INTCLR = _CFD2INT_RXIF_MASK;

        // get FIFO number
        uint8_t fifoNum = (uint8_t) CFD2VEC & _CFD2VEC_ICODE_MASK;
        if (fifoNum != 1)
            return;


        // copy data
        if (canbus_interface[1].rx_length < CAN_RX_BUFFER_LENGTH) {
            uint32_t *src = (uint32_t *) PA_TO_KVA1(*(volatile uint32_t *) (&CFD2FIFOUA1));
            unsigned pos =
                    (canbus_interface[1].rx_position + canbus_interface[1].rx_length) & (CAN_RX_BUFFER_LENGTH - 1);
            uint32_t *dst = (uint32_t *) &canbus_interface[1].rx_buffer[pos].w1;
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *dst = *src;
            canbus_interface[1].rx_length++;
        }

        /* Message processing is done, update the message buffer pointer. */
        CFD2FIFOCON1SET = _CFD2FIFOCON1_UINC_MASK;
    }
}

void __ISR(_CAN3_VECTOR, ipl2SRS)CAN3_Handler(void) {
    IFS5CLR = _IFS5_CAN3IF_MASK;
    // failure
    if (CFD3INT & _CFD3INT_SERRIF_MASK) {
        canbus_interface[2].failures |= CANBUS_FAILURE_SYSTEM_ERROR;
        CFD3INTCLR = _CFD3INT_SERRIF_MASK;
    }
    if (CFD3INT & _CFD3INT_CERRIF_MASK) {
        canbus_interface[2].failures |= CANBUS_FAILURE_BUS_ERROR;
        CFD3INTCLR = _CFD3INT_CERRIF_MASK;
    }
    if (CFD3INT & _CFD3INT_IVMIF_MASK) {
        canbus_interface[2].failures |= CANBUS_FAILURE_INVALID_MESSAGE_ERROR;
        CFD3INTCLR = _CFD3INT_IVMIF_MASK;
    }

    // message received?
    if (CFD3INT & _CFD3INT_RXIF_MASK) {
        // clear flag
        CFD3INTCLR = _CFD3INT_RXIF_MASK;

        // get FIFO number
        uint8_t fifoNum = (uint8_t) CFD3VEC & _CFD3VEC_ICODE_MASK;
        if (fifoNum != 1)
            return;


        // copy data
        if (canbus_interface[2].rx_length < CAN_RX_BUFFER_LENGTH) {
            uint32_t *src = (uint32_t *) PA_TO_KVA1(*(volatile uint32_t *) (&CFD3FIFOUA1));
            unsigned pos =
                    (canbus_interface[2].rx_position + canbus_interface[2].rx_length) & (CAN_RX_BUFFER_LENGTH - 1);
            uint32_t *dst = (uint32_t *) &canbus_interface[2].rx_buffer[pos].w1;
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *dst = *src;
            canbus_interface[2].rx_length++;
        }

        /* Message processing is done, update the message buffer pointer. */
        CFD3FIFOCON1SET = _CFD3FIFOCON1_UINC_MASK;
    }
}

void __ISR(_CAN4_VECTOR, ipl2SRS)CAN4_Handler(void) {
    IFS5CLR = _IFS5_CAN4IF_MASK;
    // failure
    if (CFD4INT & _CFD4INT_SERRIF_MASK) {
        canbus_interface[3].failures |= CANBUS_FAILURE_SYSTEM_ERROR;
        CFD4INTCLR = _CFD4INT_SERRIF_MASK;
    }
    if (CFD4INT & _CFD4INT_CERRIF_MASK) {
        canbus_interface[3].failures |= CANBUS_FAILURE_BUS_ERROR;
        CFD4INTCLR = _CFD4INT_CERRIF_MASK;
    }
    if (CFD4INT & _CFD4INT_IVMIF_MASK) {
        canbus_interface[3].failures |= CANBUS_FAILURE_INVALID_MESSAGE_ERROR;
        CFD4INTCLR = _CFD4INT_IVMIF_MASK;
    }

    // message received?
    if (CFD4INT & _CFD4INT_RXIF_MASK) {
        // clear flag
        CFD4INTCLR = _CFD4INT_RXIF_MASK;

        // get FIFO number
        uint8_t fifoNum = (uint8_t) CFD4VEC & _CFD4VEC_ICODE_MASK;
        if (fifoNum != 1)
            return;


        // copy data
        if (canbus_interface[3].rx_length < CAN_RX_BUFFER_LENGTH) {
            uint32_t *src = (uint32_t *) PA_TO_KVA1(*(volatile uint32_t *) (&CFD4FIFOUA1));
            unsigned pos =
                    (canbus_interface[3].rx_position + canbus_interface[3].rx_length) & (CAN_RX_BUFFER_LENGTH - 1);
            uint32_t *dst = (uint32_t *) &canbus_interface[3].rx_buffer[pos].w1;
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *dst = *src;
            canbus_interface[3].rx_length++;
        }

        /* Message processing is done, update the message buffer pointer. */
        CFD4FIFOCON1SET = _CFD4FIFOCON1_UINC_MASK;
    }
}