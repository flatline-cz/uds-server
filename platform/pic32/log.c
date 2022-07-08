//
// Created by tumap on 7/7/22.
//
#include <stdio.h>
#include <stdarg.h>
#include "log.h"
#include "platform-serial.h"
#include "platform-timer.h"

#define MAX_LOG_MESSAGE_LENGTH  128

static char buffer[MAX_LOG_MESSAGE_LENGTH+1];

void log_message(const char *source_file, int source_line, const char *msg, ...) {
    int len;
    
    len=snprintf(buffer, MAX_LOG_MESSAGE_LENGTH, "% 4d.%03d ", now/1000, now%1000);
    // source file/line
    if (source_file)
        len+=snprintf(buffer+len, MAX_LOG_MESSAGE_LENGTH-len, "%s(%d): ", source_file, source_line);

    // message itself
    va_list args;
    va_start(args, msg);
    len+=vsnprintf(buffer+len, MAX_LOG_MESSAGE_LENGTH-len, msg, args);
    va_end(args);

    // line terminator
    buffer[len++]='\n';

    // send via serial interface
    platform_serial_send(buffer, len);
}
