#include <vector>

#include "../../../inc/renderer/vulkan/vk_device.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_device;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_device::vk_device(const vk_instance& instance)
    : physical_device(VK_NULL_HANDLE),
    device(VK_NULL_HANDLE),
    queue(VK_NULL_HANDLE),
    queue_family(static_cast<uint32_t>(-1))
{
    pick_physical_device(instance);
    select_graphics_queue_family();
    create_logical_device();
}

vk_device::~vk_device()
{
    vkDestroyDevice(device, nullptr);
}

const VkDevice vk_device::get_device() const 
{
    return device;
}

void vk_device::pick_physical_device(const vk_instance& instance)
{
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance.get_instance(), &device_count, nullptr);
    if (device_count == 0)
    {
        _logger->fatal("Could not find a GPU with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance.get_instance(), &device_count, devices.data());

    for (const auto& device : devices)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            physical_device = device;
            _logger->info("Selected device : [" + static_cast<std::string>(properties.deviceName) + "]");
        }
    }
}

void vk_device::select_graphics_queue_family()
{
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, queue_families.data());

    uint32_t i = 0;
    for (const auto& family : queue_families)
    {
        if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            queue_family = i;
            break;
        }

        ++i;
    }
}

void vk_device::create_logical_device()
{
    const float queue_priority[] = { 1.0f };
    int device_extension_count = 1;
    const char* device_extensions[] = { "VK_KHR_swapchain" };

    VkDeviceQueueCreateInfo queue_create_info[1]{};
    queue_create_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info[0].queueFamilyIndex = queue_family;
    queue_create_info[0].queueCount = 1;
    queue_create_info[0].pQueuePriorities = queue_priority;

    VkDeviceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.queueCreateInfoCount = 1;
    create_info.pQueueCreateInfos = queue_create_info;
    create_info.enabledExtensionCount = device_extension_count;
    create_info.ppEnabledExtensionNames = device_extensions;

    if (vkCreateDevice(physical_device, &create_info, nullptr, &device) != VK_SUCCESS)
    {
        _logger->error("Failed to create logical device");
        return;
    }

    _logger->info("Successfully created logical device");
    vkGetDeviceQueue(device, queue_family, 0, &queue);
}