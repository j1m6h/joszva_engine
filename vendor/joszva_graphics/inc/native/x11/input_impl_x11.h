#ifndef INPUT_IMPL_X11_H
#define INPUT_IMPL_X11_H

#include "window_impl_x11.h"

#include "../../base/config.h"
#include "../../base/keyboard.h"
#include "../../base/mouse.h"

#include "../../math/vector2.h"

#ifdef JOSZVA_SYS_LINUX
namespace joszva::graphics::priv
{
    namespace input_impl_x11
    {
        bool is_key_pressed(keyboard::key _key);
        bool is_mouse_pressed(mouse::button btn);
        const vector2<int> get_cursor_coords();
        const vector2<int> get_cursor_coords(const window_impl_x11& win);
        void set_cursor_coords(const window_impl_x11& win, const vector2<int>& point);
    }
}
#endif
#endif