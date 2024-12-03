#pragma once

// Try to login into device, return true of false value
bool tryPassword(char* str);

// Set password on device
void setPassword(char* str);

// Get password on device
char* getPassword(void);
