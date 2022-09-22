#define KEYBOARD_MATRIX_H // disabled
#ifndef KEYBOARD_MATRIX_H
#define KEYBOARD_MATRIX_H
#include "text_buffer_debug.h"
#include "text_window_debug.h"
#include <Keypad.h>

const byte KEY_COLS = 4;
const byte KEY_ROWS = 4;
//// IO Pins
byte rowPins[KEY_ROWS] = {  3, 21, 19, 18};
byte colPins[KEY_COLS] = {  5, 17, 16,  4};
//// KeyPad
char keys[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// global
TextBuffer buffer = TextBuffer();
TextWindow window = TextWindow(&buffer);
TextBufferDebug buffer_debug = TextBufferDebug(&buffer);
TextWindowDebug window_debug = TextWindowDebug(&window);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS);

void setup() {
Serial.begin(115200);  // Allow serial output
  Serial.println("----------------------------------------");
  Serial.println("Setting up the ESP32...");
  buffer_debug.dev_buffer_init();
  window_debug.dev_window_init();
  Serial.println("Setup complete.");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '*' : buffer.move_point_home(); break;
      case '#' : buffer.move_point_end(); break;
      case 'A' : buffer.delete_characters(-1); break;
      case 'B' : buffer.delete_characters(+1); break;
      case 'C' : buffer.insert_character('\n'); break;
      case 'D' : buffer_debug.dev_buffer_init(); break;
      case '1' : buffer.insert_character('a'); break;
      case '2' : buffer.insert_character('b'); break;
      case '3' : buffer.insert_character('c'); break;
      case '4' : buffer.insert_character('x'); break;
      case '5' : buffer.window_move_point_up(WINDOW_WIDTH); break;
      case '6' : buffer.insert_character('x'); break;
      case '7' : buffer.move_point_left_explicit();  break;
      case '8' : buffer.window_move_point_down(WINDOW_WIDTH); break;
      case '9' : buffer.move_point_right_explicit(); break;
      case '0' : buffer.insert_character(' '); break;
      default  : buffer.insert_character(key);
    }
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    buffer_debug.dev_print_state();
    window.get_window();
    window_debug.dev_print_win_state();
  }
}
#endif  // KEYBOARD_MATRIX_H