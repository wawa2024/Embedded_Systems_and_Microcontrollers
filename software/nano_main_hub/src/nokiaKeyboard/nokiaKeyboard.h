#pragma once

// Key struct for nokiaKeyboard
struct nokiaKey {
  bool overwrite;
  char character;
};

nokiaKey evalNokia(char c);
// ^Evaluate character into a nokiaKey
