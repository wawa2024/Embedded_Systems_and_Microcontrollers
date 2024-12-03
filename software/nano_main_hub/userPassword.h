#pragma once

bool tryPassword(char* str);
// ^Try password on device

void setPassword(char* str);
// ^Set password on device

char* getPassword(void);
// ^Get password on device

void initPassword(void);
// ^Get password register from eeprom

void savePassword(void);
// ^Save password into eeprom
