#ifndef MOUSE_H
#define MOUSE_H

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
    }
}
#endif