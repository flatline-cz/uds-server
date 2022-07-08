//
// Created by tumap on 7/7/22.
//
#include <xc.h>
#include <sys/kmem.h>
#include "platform-serial.h"


#define ConvertToPhysicalAddress(a) ((uint32_t)KVA_TO_PA(a))


// TX buffer context
#define TX_BUFFER_LENGTH_BITS   10
#define TX_BUFFER_LENGTH        (1<<TX_BUFFER_LENGTH_BITS)

static char tx_buffer[TX_BUFFER_LENGTH];
static unsigned tx_position;
static unsigned tx_length;
static unsigned tx_dma_chunk_length;


void platform_serial_init() {
    
    // configure PPS
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;
    
//    U4RXR = 3;
    RPB11R = 2; // U4TX
    
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;
    
    /* DMA channel 1 configuration */
    DCH1CON = 0x0;
    DCH1ECON = 0x4310;
    DCH1INT = 0x0;
    
    IEC2CLR = (_IEC2_U4EIE_MASK | _IEC2_U4RXIE_MASK | _IEC2_U4TXIE_MASK);
    U4MODE = 0x60000;
    U4STASET = (_U4STA_UTXEN_MASK);
    U4BRG = 4;
    U4MODESET = _U4MODE_ON_MASK;
    
    // initialize TX context
    tx_position = 0;
    tx_length = 0;
    tx_dma_chunk_length = 0;
    
    // enable interrupts
    IPC16bits.U4EIP = 1;
    IPC16bits.U4EIS = 0;
    IFS2bits.U4EIF = 0;
    IEC2bits.U4EIE = 1;
}

bool platform_serial_handle() {
    // DMA is busy?
    if (DCH1CONbits.CHBUSY)
        return false;

    // transfer finished?
    if (tx_dma_chunk_length) {
        if (tx_length < tx_dma_chunk_length) {
            // unexpected error -> reset transfer
            tx_length = 0;
            tx_position = 0;
        } else {
            tx_length -= tx_dma_chunk_length;
            tx_position = (tx_position + tx_dma_chunk_length)&(TX_BUFFER_LENGTH - 1);
        }
        tx_dma_chunk_length = 0;
    }

    // have something to send?
    if (!tx_length)
        return false;

    // initiate DMA transfer
    register unsigned length = TX_BUFFER_LENGTH - tx_position;
    if (length > tx_length)
        length = tx_length;
    tx_dma_chunk_length = length;

    DCH1DSIZ = 1;
    DCH1SSIZ = length;
    DCH1CSIZ = 1;
    DCH1SSA = ConvertToPhysicalAddress(tx_buffer + tx_position);
    DCH1DSA = ConvertToPhysicalAddress(&U4TXREG);

    DCH1CONSET = _DCH1CON_CHEN_MASK;
    
    return true;
}

void platform_serial_send(char* message, unsigned length) {
    // check length
    if (tx_length + length > TX_BUFFER_LENGTH)
        // not sent
        return;

    // copy data
    unsigned pos = tx_position + tx_length;
    tx_length+=length;
    while (length--) {
        pos &= (TX_BUFFER_LENGTH - 1);
        tx_buffer[pos++] = *(message++);
    }

    // OK
    return;
    
}


