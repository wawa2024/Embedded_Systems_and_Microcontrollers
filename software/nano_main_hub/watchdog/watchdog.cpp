#include <Arduino.h>
#include "watchdog.h"

void wdt_ack(void)
{
    __asm__ ("WDR");
}

void wdt_init(void)
{
    __asm__ ("cli");
    wdt_ack();
    // WDE = 1, WDCE = 1
    WDTCSR |= 0x18;
    // 500ms timeout
    // WDE = 1, WDP2 = 1, WDP0 = 1
    WDTCSR = 0x0D;
    __asm__ ("sei");
}
