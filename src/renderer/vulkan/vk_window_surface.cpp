#include "../../../inc/renderer/vulkan/vk_window_surface.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_window_surface;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_window_surface::vk_window_surface(const VkInstance instance, graphics::window& win)
    : surface(VK_NULL_HANDLE),
    instance(instance)
{
    win.create_vulkan_surface(instance, nullptr, surface);
    _logger->info("Successfully created vulkan surface");
}

vk_window_surface::~vk_window_surface()
{
    vkDestroySurfaceKHR(instance, surface, nullptr);
}

const VkSurfaceKHR vk_window_surface::get_surface() const 
{
    return surface;
}