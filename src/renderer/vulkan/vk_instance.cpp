#include "renderer/vulkan/vk_instance.h"

using joszva::engine::vk_instance;

vk_instance::vk_instance(const char** extensions, uint32_t extension_count)
{
    create_instance(extensions, extension_count);
}

vk_instance::~vk_instance()
{
    cleanup();
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

    if (vkCreateInstance(&create_info, nullptr, &_vk_instance) != VK_SUCCESS)
    {
        /* failed to create instance */
        return;       
    }

    /* successfully created instance */
}

void vk_instance::cleanup()
{
    vkDestroyInstance(_vk_instance, nullptr);
}