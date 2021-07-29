#ifndef INPUT_IMPL_WIN32_H
#define INPUT_IMPL_WIN32_H

#include "window_impl_win32.h"

#include "../../base/config.h"
#include "../../base/keyboard.h"
#include "../../base/mouse.h"

#include "../../math/vector2.h"

#ifdef JOSZVA_SYS_WINDOWS
namespace joszva::graphics::priv
{
    namespace input_impl_win32
    {
        /* detect a key press, works with or without a window */
        bool is_key_pressed(keyboard::key key);
        bool is_mouse_pressed(mouse::button btn);
        /* get the root coords of cursor, cursor position on the screen */
        const vector2<int> get_cursor_coords();
        const vector2<int> get_cursor_coords(const window_impl_win32& win);
        void set_cursor_coords(const window_impl_win32& win, const vector2<int>& pt);
    };
}
#endif
#endif