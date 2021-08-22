#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace joszva::graphics
{
    namespace keyboard
    {
        /* all possible key combinations */
        enum class key
        {
            UNKNOWN = -1,
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
            NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            L_SHIFT, L_CTRL, L_ALT, L_SYSTEM, R_SHIFT, R_CTRL, R_ALT, R_SYSTEM, TAB, CAPS_LOCK, ESCAPE,
            NUMLOCK, DIVIDE, MULTIPLY, SUBTRACT, ADD, ENTER, DECIMAL,
            UP, DOWN, LEFT, RIGHT,
            INSERT, DEL, SCROLL_LOCK, HOME, END, PAUSE, PAGE_UP, PAGE_DOWN,
            PERIOD, COMMA, QUOTE, BACKSPACE, L_BRACKET, R_BRACKET, SLASH, BACKSLASH, SEMICOLON, HYPHEN, EQUAL, MENU, TILDE
        };

        bool is_key_pressed(key k);
    }
}
#endif