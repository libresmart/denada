#ifndef CONFIG_H
#define CONFIG_H

// GPIO Pins
// Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
#define PIN_I2C_SDA 18
#define PIN_I2C_SCL 19
// usb_pins_config_t {DP_P0, DM_P0, DP_P1, DM_P1, DP_P2, DM_P2, DP_P3, DM_P3}
// Good pairs (16,17),(22,23),(18,19),(13,15) -- (-1,-1) to disable
#define PIN_USB_DATA_PLUS 22
#define PIN_USB_DATA_MINUS 23

// Storage (in bytes)
#define GAP_BUFFER_RAW_SIZE 1024
#define BUFFER_FILENAME_SIZE 256
#define BUFFER_NAME_SIZE 256
#define KEYBOARD_BUFFER_SIZE 256

// Display
#define FIRST_COLUMN_NUMBER 1
#define FIRST_LINE_NUMBER 1
#define TAB_SIZE 4
#define WINDOW_HEIGHT 4
#define WINDOW_WIDTH 40

// Special Characters
#define CHAR_EOL '\n'
#define CHAR_NUL '\0'
#define CHAR_SPC ' '
#define CHAR_TAB '\t'
// debug
#define CHAR_EOL_DISPLAY '='
#define CHAR_NUL_DISPLAY '.'
#define CHAR_SPC_DISPLAY '_'
#define CHAR_TAB_DISPLAY '~'

// USB
// USB KeyBoard - ESP32-Wroom
//#define PROFILE_NAME "Default Wroom"
//#define DEBUG_ALL

#endif // CONFIG_H