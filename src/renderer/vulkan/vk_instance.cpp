#include <vector>

#include "../../../inc/renderer/vulkan/vk_instance.h"

#include "../../../vendor/joszva_log/inc/logger.h"
#include "../../../vendor/joszva_graphics/inc/base/window.h"

using joszva::engine::vk_instance;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_instance::vk_instance()
    : instance(VK_NULL_HANDLE)
{
    /* some basic information about our application */
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Joszva_Engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Joszva_Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    uint32_t extension_count = 0;
    const char** extensions = graphics::window::get_required_instance_extensions(&extension_count);

    std::vector<const char*> enabled_instance_extensions{};
    for (size_t i = 0; i < extension_count; ++i)
    {
        enabled_instance_extensions.push_back(extensions[i]);
    }

    create_info.enabledExtensionCount = static_cast<uint32_t>(enabled_instance_extensions.size());
    create_info.ppEnabledExtensionNames = enabled_instance_extensions.data();
    create_info.enabledLayerCount = 0;

    if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
    {
        _logger->error("Failed to create vulkan instance");
        return;       
    }

    _logger->info("Successfully created vulkan instance");
}

vk_instance::~vk_instance()
{
    vkDestroyInstance(instance, nullptr);
}

const VkInstance vk_instance::get_instance() const 
{
    return instance;
}