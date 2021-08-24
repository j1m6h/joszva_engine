#include "../../../inc/renderer/vulkan/vk_instance.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_instance;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_instance::vk_instance()
    : instance(VK_NULL_HANDLE)
{
}

vk_instance::~vk_instance()
{
    vkDestroyInstance(instance, nullptr);
}

const VkInstance vk_instance::get_instance() const 
{
    return instance;
}

void vk_instance::init(const char** extensions, uint32_t extension_count)
{
    create_instance(extensions, extension_count);
}

void vk_instance::create_instance(const char** extensions, uint32_t extension_count)
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

    create_info.enabledExtensionCount = extension_count;
    create_info.ppEnabledExtensionNames = extensions;
    create_info.enabledLayerCount = 0;

    if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
    {
        _logger->error("Failed to create vulkan instance");
        return;       
    }

    _logger->info("Successfully created vulkan instance");
}