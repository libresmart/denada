#ifndef TEXT_BUFFER_DEBUG_H
#define TEXT_BUFFER_DEBUG_H
#include "text_buffer.h"
#include <algorithm>
#include <Arduino.h>

class TextBufferDebug {
    public:
    TextBuffer* buffer;
    TextBufferDebug(TextBuffer*);

    void dev_buffer_init();
    char dev_debug_char(int, char);
    char dev_safe_print(char);
    void dev_hr(int);
    void dev_print_buffer();
    void dev_print_status_line();
    void dev_print_state();


};
#endif  // TEXT_BUFFER_DEBUG_H



