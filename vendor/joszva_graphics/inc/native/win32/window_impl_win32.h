#ifndef WINDOW_IMPL_WIN32_H
#define WINDOW_IMPL_WIN32_H

#include <string>

#include "../../base/config.h"
#include "../../base/keyboard.h"

#include "../../math/vector2.h"

#ifdef JOSZVA_SYS_WINDOWS
namespace joszva::graphics::priv
{
    /* win32 window implementation */
    class window_impl_win32
    {
    public:
        window_impl_win32(const std::string& title, int width, int height);
        ~window_impl_win32();

        const HWND get_handle() const;
        void set_visible(bool visible);
        const std::string& get_title() const;
        void set_title(const std::string& title);
        vector2<int> get_size() const;
        void set_size(const vector2<int>& size);

        void process_events();

    private:
        void init_win32(const std::string& title, int width, int height);
        void process_event(UINT msg, WPARAM wparam, LPARAM lparam);
        void set_mouse_tracking(bool tracking);
        keyboard::key virtual_to_key(WPARAM key, LPARAM flags);

        static LRESULT CALLBACK initial_procedure(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam);

        HWND handle;
        std::string title;
        /* original event callback */
        LONG_PTR callback;
        bool mouse_inside;
    };
}
#endif
#endif