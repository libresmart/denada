#ifndef LCD_H
#define LCD_H

#include "text_buffer.h"
#include <SerLCD.h>
void display_text(SerLCD *lcd, TextBuffer *text_buffer)
{
    int buffer_length = text_buffer->content_size();
    lcd->clear();
    for (int line = 0; line < 4 && line * 20 < buffer_length; line++)
    {
        bool line_full = buffer_length >= 20 + line * 20;
        int line_length = (line_full) ? 20 : buffer_length % 20;
        for (int i = (line * 20); i < line_length + (line * 20); i++)
        {
            lcd->write(text_buffer->get_character(i));
        }
        if (line_full && line < 3)
            lcd->setCursor(0, line + 1);
    }
    if (buffer_length >= 80)
        lcd->setCursor(19, 3);
}
void display_config(SerLCD *lcd)
{
    lcd->disableSystemMessages();      // Remove vendor branding
    lcd->setContrast(128);             // 0-255 0 is highest contrast
    lcd->setFastBacklight(64, 64, 64); // 0-255 R,G,B
    lcd->clear();
    lcd->setCursor(0, 1);
    lcd->print(" LibreSmart DeNada");
    lcd->blink();
}

#endif // LCD_H