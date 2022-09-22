#ifndef TEXT_WINDOW_DEBUG_H
#define TEXT_WINDOW_DEBUG_H
#include "text_window.h"
#include <Arduino.h>

class TextWindowDebug {
    public:
    TextWindow* window;
    TextWindowDebug(TextWindow*);
    void dev_window_init();
    char dev_win_safe_print(char);
    void dev_hr(int);
    void dev_print_win_state();
};
#endif  // TEXT_WINDOW_DEBUG_H