#ifndef KEYBOARD_USB_H
#define KEYBOARD_USB_H
/**
 * References: https://github.com/felis/USB_Host_Shield_2.0
 */
#include "config.h"
#include "text_buffer.h"
#include "keyboard_buffer_usb.h"
#include "keycodes_usb.h"
#include <pgmspace.h>
#include <cstdint>
#include <cstdio>
#define VALUE_BETWEEN(v, l, h) (((v) > (l)) && ((v) < (h)))
#define VALUE_WITHIN(v, l, h) (((v) >= (l)) && ((v) <= (h)))

struct MODIFIERKEYS
{
    uint8_t bmLeftCtrl : 1;
    uint8_t bmLeftShift : 1;
    uint8_t bmLeftAlt : 1;
    uint8_t bmLeftGUI : 1;
    uint8_t bmRightCtrl : 1;
    uint8_t bmRightShift : 1;
    uint8_t bmRightAlt : 1;
    uint8_t bmRightGUI : 1;
};

struct KBDINFO
{
    struct
    {
        uint8_t bmLeftCtrl : 1;
        uint8_t bmLeftShift : 1;
        uint8_t bmLeftAlt : 1;
        uint8_t bmLeftGUI : 1;
        uint8_t bmRightCtrl : 1;
        uint8_t bmRightShift : 1;
        uint8_t bmRightAlt : 1;
        uint8_t bmRightGUI : 1;
    };
    uint8_t bReserved;
    uint8_t Keys[KBDINFO_MAX_KEYS];
};

struct KBDLEDS
{
    uint8_t bmNumLock : 1;
    uint8_t bmCapsLock : 1;
    uint8_t bmScrollLock : 1;
    uint8_t bmCompose : 1;
    uint8_t bmKana : 1;
    uint8_t bmReserved : 3;
};

class KeyboardInputHandler
{
    static const uint8_t numKeys[10];
    static const uint8_t symKeysUp[12];
    static const uint8_t symKeysLo[12];
    static const uint8_t padKeys[5];

protected:
    union
    {
        KBDINFO kbdInfo;
        uint8_t bInfo[sizeof(KBDINFO)];
    } prevState;

    union
    {
        KBDLEDS kbdLeds;
        uint8_t bLeds;
    } kbdLockingKeys;

public:
    KeyboardInputHandler()
    {
        // bLeds = 0;
        bmCapsLock = false;
        bmNumLock = false;
        bmScrollLock = false;
    };

    bool bmCapsLock;
    bool bmNumLock;
    bool bmScrollLock;

    uint8_t OemToAscii(uint8_t mod, uint8_t key);
    void Parse(uint8_t len, uint8_t *buf, TextBuffer *text_buffer);

protected:
    virtual uint8_t HandleLockingKeys(uint8_t key)
    {
        if (key == KEY_NUMLOCK)
            bmNumLock = !bmNumLock;
        if (key == KEY_CAPSLOCK)
            bmCapsLock = !bmCapsLock;
        if (key == KEY_SCROLLLOCK)
            bmScrollLock = !bmScrollLock;
        return 0;
    };

    virtual void OnControlKeysChanged(uint8_t before __attribute__((unused)), uint8_t after __attribute__((unused))){};
    virtual void OnKeyDown(uint8_t mod __attribute__((unused)), uint8_t key __attribute__((unused))){};
    virtual void OnKeyUp(uint8_t mod __attribute__((unused)), uint8_t key __attribute__((unused))){};
    virtual const uint8_t *getNumKeys() { return numKeys; };
    virtual const uint8_t *getSymKeysUp() { return symKeysUp; };
    virtual const uint8_t *getSymKeysLo() { return symKeysLo; };
    virtual const uint8_t *getPadKeys() { return padKeys; };
};

#endif // KEYBOARD_USB_H