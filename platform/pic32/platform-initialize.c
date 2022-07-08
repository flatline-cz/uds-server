#include <xc.h>

static void CLK_Initialize(void) {
    /* unlock system for clock configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;


    REFO1CON = 0x10200;
    REFO1TRIM = 0x80000000;
    REFO1CONSET = 0x00008000;

    REFO4CON = 0x10200;
    REFO4TRIM = 0x80000000;
    REFO4CONSET = 0x00008000;

    /* Peripheral Module Disable Configuration */
    PMD1 = 0x00000131;
    PMD2 = 0x0017001f;
    PMD3 = 0xffffffff;
    PMD4 = 0x0fff01f5;
    PMD5 = 0x030e3f36;
    PMD6 = 0x0f0d0000;
    PMD7 = 0x00000000;

    /* Lock system since done with clock configuration */
    SYSKEY = 0x33333333;
}

static void DMAC_Initialize() {
    /* Enable the DMA module */
    DMACONSET = _DMACON_ON_MASK;

    /* DMACON register */
    /* ON = 1          */
    DMACON = 0x8000;
}

static void EVIC_Initialize(void) {
    INTCONSET = _INTCON_MVEC_MASK;

    /* Configure Shadow Register Set */
    PRISS = 0x76543210;
}

static void GPIO_Initialize(void) {
    /* PORTA Initialization */

    /* PORTB Initialization */
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB9 = 0;
    TRISBbits.TRISB9 = 0;


    /* PORTC Initialization */
    ANSELCbits.ANSC0 = 0;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSC1 = 0;
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC6 = 0;


    /* PORTD Initialization */

    /* PORTE Initialization */

    /* PORTF Initialization */

    /* PORTG Initialization */
    ANSELGCLR = 0x180; /* Digital Mode Enable */


    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    /* PPS Input Remapping */
    C1RXR = 6;
    C2RXR = 4;
    C3RXR = 5;
    C4RXR = 2;
    U4RXR = 3;
    U1RXR = 3;

    /* PPS Output Remapping */
    RPC0R = 12; // C1TX
    RPB9R = 12; // C2TX
    RPC6R = 12; // C3TX
    RPB1R = 12; // C4TX

    RPB11R = 2; // U4TX
    RPB15R = 1; // U1TX

    /* Lock back the system after PPS configuration */
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;

}


void platform_initialize() {
    /* Start out with interrupts disabled before configuring any modules */
    __builtin_disable_interrupts();


    CLK_Initialize();

    /* Configure CP0.K0 for optimal performance (cached instruction pre-fetch) */
    __builtin_mtc0(16, 0, (__builtin_mfc0(16, 0) | 0x3));

    /* Configure Wait States and Prefetch */
    CHECONbits.PFMWS = 2;
    CHECONbits.PREFEN = 1;
    CHECONbits.PERCHEEN=0;


//    GPIO_Initialize();

    DMAC_Initialize();

    EVIC_Initialize();
    
}

