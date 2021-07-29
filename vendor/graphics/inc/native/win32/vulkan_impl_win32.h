#ifndef VULKAN_IMPL_WIN32_H
#define VULKAN_IMPL_WIN32_H

#include <vulkan/vulkan.h>

#include "window_impl_win32.h"

#ifdef JOSZVA_SYS_WINDOWS
namespace joszva::graphics::priv
{
	namespace vulkan_impl_win32
	{
		const char** get_required_instance_extensions(uint32_t* count);
		VkResult create_vulkan_surface(const window_impl_win32& win, const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR& surface);
	}
}
#endif
#endif