#include "text_window.h"

TextWindow::TextWindow(TextBuffer* text_buffer) {
    buffer = text_buffer;
    clear();
}

void TextWindow::clear() {
    win_start = 0;
    cursor_row = 0;
    cursor_col = 0;
    // contents
    std::fill_n(&contents[0][0], WINDOW_HEIGHT * WINDOW_WIDTH, 0);
}

void TextWindow::get_window() {
  int char_loc = win_start;
  char character = CHAR_NUL;
  for (int i = 0; i < WINDOW_HEIGHT; i++) {
    for (int j = 0; j < WINDOW_WIDTH; j++) {
      if (buffer->get_point() == char_loc) {
        cursor_row = i;
        cursor_col = j;
      }
      character = buffer->get_character(char_loc);
      if (char_loc < buffer->content.max_index()) {
        char_loc++;
      }
      contents[i][j] = character;
      if (character == CHAR_EOL) {
        for (;j < WINDOW_WIDTH; j++) {
          contents[i][j] = CHAR_NUL;
        }
      }
      if (character == CHAR_TAB) {
        int tab_excess = (j + TAB_SIZE) % TAB_SIZE;
        int next_stop = j + TAB_SIZE - tab_excess;
        for (;j < next_stop && j < WINDOW_WIDTH; j++) {
          contents[i][j] = CHAR_NUL;
        }
        j--;
      }
    }
  }
}
