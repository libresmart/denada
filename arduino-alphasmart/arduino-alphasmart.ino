// Inspiration: AlphaSmart Neo
/*
 * Depends on:
 *    ESP32-USBSoftHost.hpp
 *    SerLCD.h
 *    Wire.h
 */
#include "src/text_buffer.h"
#include "src/text_buffer_debug.h"
#include "src/text_window.h"
#include "src/text_window_debug.h"
#include "src/keyboard_usb.h"
#include "src/lcd.h"
#include "src/usb_debug.h"
#include <ESP32-USBSoftHost.hpp> // USH (also starts FreeRTOS)
#include <Wire.h>                // Wire
#include <SerLCD.h>              // SerLCD

SerLCD lcd;
TextBuffer text_buffer;
TextWindow text_window(&text_buffer);
TextBufferDebug buffer_debug(&text_buffer);
TextWindowDebug window_debug(&text_window);
KeyboardInputHandler keyboard_handler;
KeyboardInputBuffer keyboard_buffer;
static void process_keyboard_input(uint8_t *data)
{
    keyboard_handler.Parse(KBDINFO_SIZE, data, &text_buffer);
}
TaskHandle_t read_buffer_handle;
static void read_buffer_task()
{
    for (;;)
    {
        vTaskDelay(1);
        if (keyboard_buffer.is_empty())
            continue;
        while (!keyboard_buffer.is_empty())
            process_keyboard_input((uint8_t *)keyboard_buffer.read().data);
        display_text(&lcd, &text_buffer);
    }
}
static void usb_status(uint8_t usbNum, void *dev)
{
#ifdef USB_DEBUG_H
    usb_status_display(usbNum, dev);
#endif
}
static void usb_input(uint8_t usbNum, uint8_t byte_depth, uint8_t *data, uint8_t data_len)
{
    keyboard_buffer.write(data);
}
void setup()
{
    Serial.begin(115200);
    usb_pins_config_t usb_config = {PIN_USB_DATA_PLUS, PIN_USB_DATA_MINUS, -1, -1, -1, -1, -1, -1};
    USH.init(usb_config, usb_status, usb_input);
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    Wire.setClock(400000);
    lcd.begin(Wire); // Setup LCD with I2C
    display_config(&lcd);
    xTaskCreate((TaskFunction_t)read_buffer_task, "read_buffer_task", 2048, NULL, 5, &read_buffer_handle);
}

void loop()
{
    vTaskDelete(NULL);
}
