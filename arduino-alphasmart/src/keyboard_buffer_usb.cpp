#include "keyboard_buffer_usb.h"

KeyboardInputBuffer::KeyboardInputBuffer()
{
    //std::fill_n((uint8_t*)&reports[0], KEYBOARD_BUFFER_SIZE, 0);
    write_index = 0;
    read_index = 0;
}

void KeyboardInputBuffer::write(uint8_t *data)
{
    // This function has no buffer over/underrun protection
    for (int i = 0; i < KBDINFO_SIZE; i++)
        reports[write_index].data[i] = data[i];
    write_index = (write_index + 1) % HID_BUFFER_SIZE;
}
struct keyboard_input_report KeyboardInputBuffer::read()
{
    // This function has no buffer over/underrun protection
    struct keyboard_input_report hid_report;
    for (int i = 0; i < KBDINFO_SIZE; i++)
        hid_report.data[i] = reports[read_index].data[i];
    read_index = (read_index + 1) % HID_BUFFER_SIZE;
    return hid_report;
}
bool KeyboardInputBuffer::is_empty()
{
    return (read_index == write_index);
}
int KeyboardInputBuffer::buffer_usage(){
    return (HID_BUFFER_SIZE + write_index - read_index) % HID_BUFFER_SIZE;
}
