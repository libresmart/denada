#include "Keypad.h"

const byte KEY_COLS   =    4;
const byte KEY_ROWS   =    4;

//// IO Pins
byte rowPins[KEY_ROWS] = { 3, 21, 19, 18};
byte colPins[KEY_COLS] = { 5, 17, 16,  4};

//// KeyPad
char keys[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS);
