#ifndef VULKAN_IMPL_X11_H
#define VULKAN_IMPL_X11_H

#include <vector>
/* need to include Xlib.h first, then vulkan.h and finally vulkan_xlib.h otherwise 
    there will be errors due to vulkan_xlib.h requiring Xlib.h to be defined first */
#include "../../base/config.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>
/*  */

#include "window_impl_x11.h"

#ifdef JOSZVA_SYS_LINUX
namespace joszva::graphics::priv
{
    namespace vulkan_impl_x11
    {
        const char** get_required_instance_extensions(uint32_t* count);
        VkResult create_vulkan_surface(const window_impl_x11& win, const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR& surface);
    }
}
#endif
#endif