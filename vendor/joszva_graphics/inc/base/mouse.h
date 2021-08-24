#ifndef MOUSE_H
#define MOUSE_H

#include "../math/vector2.h"

namespace joszva::graphics
{
    namespace mouse
    {
        enum class button
        {
            LEFT,
            RIGHT,
            MIDDLE,
            EXTRA1,
            EXTRA2
        };

        bool is_mouse_pressed(mouse::button btn);
        const vector2<int> get_cursor_coords();
    }
}
#endif