#ifndef KEYBOARD_BUFFER_USB_H
#define KEYBOARD_BUFFER_USB_H

#include "config.h"
#include <cstdint>
#define KBDINFO_SIZE 8
#define KBDINFO_MODIFIERS_INDEX 0
#define KBDINFO_FIRST_KEY_INDEX 2
#define KBDINFO_MAX_KEYS (KBDINFO_SIZE - KBDINFO_FIRST_KEY_INDEX)
#define HID_BUFFER_SIZE (KEYBOARD_BUFFER_SIZE / KBDINFO_SIZE)

struct keyboard_input_report
{
    uint8_t data[KBDINFO_SIZE];
};

class KeyboardInputBuffer
{
public:
    struct keyboard_input_report reports[HID_BUFFER_SIZE];
    volatile int write_index;
    volatile int read_index;

    KeyboardInputBuffer();
    void write(uint8_t *data);
    struct keyboard_input_report read();
    bool is_empty();
    int buffer_usage();
};

#endif // KEYBOARD_BUFFER_USB_H