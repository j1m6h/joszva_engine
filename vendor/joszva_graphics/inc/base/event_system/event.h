#ifndef EVENT_H
#define EVENT_H

#include <functional>

namespace joszva::graphics
{
    template<typename T>
    using event_function = std::function<void(const T& _event)>;

    class event
    {
    public:
        // all possible event types
        enum event_type
        {
            LOAD, RESIZE, CLOSE,
            KEY_PRESSED, KEY_RELEASED,
            MOUSE_MOTION, MOUSE_ENTER, MOUSE_LEAVE, MOUSE_PRESSED, MOUSE_RELEASED,
            NONE
        };
    };
}
#endif