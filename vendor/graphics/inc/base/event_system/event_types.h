#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include "event.h"
#include "../keyboard.h"
#include "../mouse.h"

namespace joszva::graphics
{
    /* all possible events structures */

    struct size_event
    {
        static const event::event_type type()
        { return event::RESIZE; }

        int x;
        int y;
        int width;
        int height;
    };

    struct close_event
    {
        static const event::event_type type()
        { return event::CLOSE; }
    };

    struct mouse_motion_event
    {
        static const event::event_type type() 
        { return event::MOUSE_MOTION; }

        int x;
        int y;
    };

    struct mouse_enter_event
    {
        static const event::event_type type()
        { return event::MOUSE_ENTER; }
    };

    struct mouse_leave_event
    {
        static const event::event_type type()
        { return event::MOUSE_LEAVE; }
    };

    struct mouse_pressed_event
    {
        static const event::event_type type()
        { return event::MOUSE_PRESSED; }

        mouse::button btn;
        int x;
        int y;
    };

    struct mouse_released_event
    {
        static const event::event_type type()
        { return event::MOUSE_RELEASED; }

        mouse::button btn;
        int x;
        int y;
    };

    struct key_pressed_event
    {
        static const event::event_type type()
        { return event::KEY_PRESSED; }

        keyboard::key key;
    };

    struct key_released_event
    {
        static const event::event_type type()
        { return event::KEY_RELEASED; }

        keyboard::key key;
    };
}
#endif