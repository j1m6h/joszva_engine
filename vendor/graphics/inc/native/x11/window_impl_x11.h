#ifndef WINDOW_IMPL_X11_H
#define WINDOW_IMPL_X11_H

#include <deque>
#include <string>

#include "display_x11.h"

#include "../../base/config.h"
#include "../../base/keyboard.h"

#include "../../math/vector2.h"

#ifdef JOSZVA_SYS_LINUX
namespace joszva::graphics::priv
{
    /* X11 window implementation */
    class window_impl_x11
    {
    public:
        window_impl_x11(const std::string& title, int width, int height);
        ~window_impl_x11();

        const Window get_handle() const;
        void set_visible(bool visible);
        const std::string& get_title() const;
        void set_title(const std::string& title);
        vector2<int> get_size() const;
        void set_size(const vector2<int>& size);
        void set_key_repeat(bool enabled);

        void process_events();
        void wait_events();

    private:
        void init_x11(const std::string& title, int width, int height);
        void set_protocols();
        bool process_event(XEvent& event);
        bool wait_for_event(double* timeout);
        keyboard::key keysym_to_key(KeySym sym);

        Display* display;
        Window handle;
        std::string title;
        /* hold current X events */
        std::deque<XEvent> events;
        bool key_repeat;
    };

    /* use this as a unary function to help detect if a key is being held */
    struct key_repeat_finder
    {
        key_repeat_finder(unsigned int keycode, Time time) : keycode(keycode), time(time) {}

        /* Predicate operator that checks event type, keycode and timestamp */
        bool operator()(const XEvent &event)
        {
            return ((event.type == KeyPress) && (event.xkey.keycode == keycode) && (event.xkey.time - time < 2));
        }

        unsigned int keycode;
        Time time;
    };
}
#endif
#endif