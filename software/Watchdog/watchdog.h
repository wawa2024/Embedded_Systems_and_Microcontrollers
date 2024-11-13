#pragma once

// resets the watchdog timer
void wdt_ack(void);

// initializes the watchdog with
// 500ms timeout
void wdt_init(void);
