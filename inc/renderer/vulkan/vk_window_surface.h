#ifndef VK_WINDOW_SURFACE_H
#define VK_WINDOW_SURFACE_H

#include <vulkan/vulkan.h>

#include "vk_instance.h"

#include "../../../vendor/joszva_graphics/inc/base/window.h"

namespace joszva::engine
{
    class vk_window_surface
    {
    public:
        vk_window_surface(const VkInstance instance, graphics::window& win);
        ~vk_window_surface();

        const VkSurfaceKHR get_surface() const;

    private:
        VkSurfaceKHR surface;
        VkInstance instance;
    };
}
#endif