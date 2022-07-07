//
// Created by tumap on 7/7/22.
//
#include <xc.h>
#include "uds-server.h"

tTime now;


void timer_init() {
    now=0;

    T2CONCLR = _T2CON_ON_MASK;
    T2CON = 0x0;
    TMR2 = 0x0;
    PR2 = 59999U;
    T2CONSET = _T2CON_ON_MASK;
    IFS0bits.T2IF=0;
}


void timer_handle() {
    // 1ms period ellapsed?
    if(IFS0bits.T2IF) {
        IFS0bits.T2IF=0;
        now++;
    }
}

tTime uds_server_get_time() {
    return now;
}
