#include <xc.h>
#include "log.h"
#include "platform-initialize.h"
#include "platform-timer.h"
#include "platform-serial.h"
//#include "platform-storage.h"
#include "platform-canbus.h"
#include "uds-server.h"


int main() {
    
    // platform initialization
    platform_initialize();
    platform_timer_init();
    platform_serial_init();
    platform_canbus_init();
//    platform_storage_init();
    
    platform_timer_handle();
    LOG_INFO("==== platform initialized ====");
    __builtin_enable_interrupts();
    
    // UDS server initialization
    uds_server_init();
   
    
    platform_timer_handle();
    LOG_INFO("==== UDS server initialized ====");
    
    
    while(1) {
        // platform handling
        platform_timer_handle();
        platform_serial_handle();
        platform_canbus_handle();
//        platform_storage_handle();
        
        // UDS server handling
        
    }
    
}
