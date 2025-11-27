#include "debug.h"
#include "uart.h"

void printDebug(const char* data) {
    UART uart = UART();

    uart.ecrireString(data);
}