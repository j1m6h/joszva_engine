#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vulkan/vulkan.h>

#include "window_impl.h"

#include "event_system/event.h"
#include "event_system/event_dispatcher.h"

#include "../math/vector2.h"

namespace joszva::graphics
{
    /* base window implementation */
    class window
    {
    public:
        window(const std::string& title, int width, int height);
        ~window();

        void set_visible(bool visible) const;
        const std::string& get_title() const;
        void set_title(const std::string& title);
        vector2<int> get_size() const;
        void set_size(const vector2<int>& size);
        const vector2<int> get_cursor_coords() const;
        void set_cursor_coords(const vector2<int>& coord) const;
        void destroy();

        const char** get_required_instance_extensions(uint32_t* count);
        VkResult create_vulkan_surface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR& surface);

        bool is_open();
        void process_events();

        /* Template argument 'event' is the specific event that is to be handled
        Example usage is as follows :
            my_window.on< mouse_motion_event >([](const auto& event_data){
                ...
            });   
        */
        template<typename event>
        void on(const event_function<event>& func)
        {
            priv::event_dispatcher<event>::instance()->subscribe(event::type(), func);
        }

    private:
        priv::window_impl* impl;
    };
}
#endif