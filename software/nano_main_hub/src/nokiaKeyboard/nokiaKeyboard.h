#pragma once

// Key struct for nokiaKeyboard
struct Key {
  bool overwrite;
  char character;
};

// Evaluate character into Key
Key evalKey(char c);
