//
// Created by tumap on 7/7/22.
//
#include <stdio.h>
#include <stdarg.h>
#include "log.h"
#include "platform-serial.h"

#define MAX_LOG_MESSAGE_LENGTH  128

static char buffer[MAX_LOG_MESSAGE_LENGTH+1];

void log_message(const char *source_file, int source_line, const char *msg, ...) {
    int len;
    // source file/line
    if (source_file)
        len=snprintf(buffer, MAX_LOG_MESSAGE_LENGTH, "%s(%d): ", source_file, source_line);
    else
        len=0;

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
