#ifndef TEXT_WINDOW_H
#define TEXT_WINDOW_H
#include "text_buffer.h"

class TextWindow {
  public:
    int win_start;
    int cursor_row;
    int cursor_col;
    TextBuffer* buffer;
    char contents[WINDOW_HEIGHT][WINDOW_WIDTH];

    TextWindow(TextBuffer*);
    void clear();
    void get_window();
};

#endif  // TEXT_WINDOW_DEBUG_H