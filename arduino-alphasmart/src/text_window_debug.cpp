#include "text_window_debug.h"

TextWindowDebug::TextWindowDebug(TextWindow *text_window) {
    window = text_window;
}

void TextWindowDebug::dev_window_init() {
  window->clear();
}
char TextWindowDebug::dev_win_safe_print(char inChar) {
  switch (inChar) {
    case CHAR_TAB : return CHAR_TAB_DISPLAY;
    case CHAR_NUL : return CHAR_NUL_DISPLAY;
    case CHAR_EOL : return CHAR_EOL_DISPLAY;
    case CHAR_SPC : return CHAR_SPC_DISPLAY;
    default : return inChar;
  }
}
void TextWindowDebug::dev_hr(int len) {
  for (int i = 0; i < len; i++) {
    Serial.print('-');
  }
}

void TextWindowDebug::dev_print_win_state() {
  int loc = window->win_start;
  Serial.print("+");
  dev_hr(WINDOW_WIDTH);
  Serial.println("+");
  for (int i = 0; i < WINDOW_HEIGHT; i++) {
    Serial.print("|");
    for (int j = 0; j < WINDOW_WIDTH; j++) {
      char character = window->contents[i][j];
      if (window->cursor_row == i && window->cursor_col == j) {
        character = '*';
      }
      Serial.print(dev_win_safe_print(character));
    }
    Serial.println("|");
  }
  Serial.print("+");
  dev_hr(WINDOW_WIDTH);
  Serial.println("+");
}
