#include "keyboard_usb.h"

const uint8_t KeyboardInputHandler::numKeys[10] PROGMEM = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};
const uint8_t KeyboardInputHandler::symKeysUp[12] PROGMEM = {'_', '+', '{', '}', '|', '~', ':', '"', '~', '<', '>', '?'};
const uint8_t KeyboardInputHandler::symKeysLo[12] PROGMEM = {'-', '=', '[', ']', '\\', ' ', ';', '\'', '`', ',', '.', '/'};
const uint8_t KeyboardInputHandler::padKeys[5] PROGMEM = {'/', '*', '-', '+', CHAR_EOL};

void KeyboardInputHandler::Parse(uint8_t len, uint8_t *buf, TextBuffer *text_buffer)
{
    if (buf[KBDINFO_FIRST_KEY_INDEX] == KEY_ERR_OVF)
        return;
    // provide event for changed control key state
    if (prevState.bInfo[KBDINFO_MODIFIERS_INDEX] != buf[KBDINFO_MODIFIERS_INDEX])
    {
        OnControlKeysChanged(prevState.bInfo[KBDINFO_MODIFIERS_INDEX], buf[KBDINFO_MODIFIERS_INDEX]);
    }

    for (uint8_t i = KBDINFO_FIRST_KEY_INDEX; i < KBDINFO_SIZE; i++)
    {
        bool down = false;
        bool up = false;

        for (uint8_t j = KBDINFO_FIRST_KEY_INDEX; j < KBDINFO_SIZE; j++)
        {
            if (buf[i] == prevState.bInfo[j] && buf[i] != KEY_ERR_OVF)
                down = true;
            if (buf[j] == prevState.bInfo[i] && prevState.bInfo[i] != KEY_ERR_OVF)
                up = true;
        }
        if (!down)
        {
            HandleLockingKeys(buf[i]);
            OnKeyDown(buf[KBDINFO_MODIFIERS_INDEX], buf[i]);
            char character = (char)OemToAscii(buf[KBDINFO_MODIFIERS_INDEX], buf[i]);
            if (character != 0)
                text_buffer->insert_character(character);
            switch (buf[i])
            {
            case KEY_BACKSPACE:
                text_buffer->delete_characters(-1);
            }
        }
        if (!up)
        {
            OnKeyUp(prevState.bInfo[KBDINFO_MODIFIERS_INDEX], prevState.bInfo[i]);
        }
    }
    for (uint8_t i = 0; i < KBDINFO_SIZE; i++)
        prevState.bInfo[i] = buf[i];
}

uint8_t KeyboardInputHandler::OemToAscii(uint8_t mod, uint8_t key)
{
    uint8_t shift = (mod & (KEY_MOD_LSHIFT | KEY_MOD_RSHIFT));
    if (VALUE_WITHIN(key, KEY_A, KEY_Z) && (bmCapsLock || shift)) // Letters Upper Case
        return (key - KEY_A + 'A');
    if (VALUE_WITHIN(key, KEY_A, KEY_Z) && !(bmCapsLock || shift)) // Letters Lower Case
        return (key - KEY_A + 'a');
    if (VALUE_WITHIN(key, KEY_1, KEY_0) && (shift)) // Number Row Symbols
        return ((uint8_t)pgm_read_byte(&getNumKeys()[key - KEY_1]));
    if (VALUE_WITHIN(key, KEY_1, KEY_0) && !(shift)) // Number Row Numbers
        return ((key == KEY_0) ? '0' : key - KEY_1 + '1');
    if (key == KEY_ENTER) // Enter Key
        return (CHAR_EOL);
    if (key == KEY_SPACE) // Spacebar
        return (CHAR_SPC);
    if (VALUE_WITHIN(key, KEY_MINUS, KEY_SLASH) && (shift)) // Symbols "Upper"
        return (uint8_t)pgm_read_byte(&getSymKeysUp()[key - KEY_MINUS]);
    if (VALUE_WITHIN(key, KEY_MINUS, KEY_SLASH) && !(shift)) // Symbols Base
        return (uint8_t)pgm_read_byte(&getSymKeysLo()[key - KEY_MINUS]);
    if (VALUE_WITHIN(key, KEY_KPSLASH, KEY_KPENTER)) // Keypad Symbols
        return (uint8_t)pgm_read_byte(&getPadKeys()[key - KEY_KPSLASH]);
    if (VALUE_WITHIN(key, KEY_KP1, KEY_KP0) && bmNumLock) // Keypad Numbers
        return ((key == KEY_KP0) ? '0' : key - KEY_KP1 + '1');
    if ((key == KEY_KPDOT) && (bmNumLock)) // Keypad Dot
        return ('.');
    // safe default for unknown keys
    return (0);
}
