//
// Created by tumap on 7/7/22.
//
#include <xc.h>
#include "platform.h"
#include "platform-timer.h"

tTime now;


void platform_timer_init() {
    now=0;

    T2CONCLR = _T2CON_ON_MASK;
    T2CON = 0x0;
    TMR2 = 0x0;
    PR2 = 59999U;
    T2CONSET = _T2CON_ON_MASK;
    IFS0bits.T2IF=0;
}


bool platform_timer_handle() {
    // 1 millisecond period elapsed?
    if(IFS0bits.T2IF) {
        IFS0bits.T2IF=0;
        now++;
        return true;
    }
    return false;
}


tTime uds_server_get_time() {
    return now;
}
