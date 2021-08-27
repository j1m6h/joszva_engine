#include <set>
#include <vector>

#include "../../../inc/renderer/vulkan/vk_device.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_device;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_device::vk_device(const VkInstance instance, const VkSurfaceKHR surface)
    : physical_device(VK_NULL_HANDLE),
    device(VK_NULL_HANDLE),
    graphics_queue(VK_NULL_HANDLE),
    present_queue(VK_NULL_HANDLE),
    queue_indicies(queue_family_indicies())
{
    pick_physical_device(instance);
    get_device_queue_indicies(surface);
    create_logical_device();
}

vk_device::~vk_device()
{
    vkDestroyDevice(device, nullptr);
}

const VkPhysicalDevice vk_device::get_physical_device() const
{
    return physical_device;
}

const VkDevice vk_device::get_device() const 
{
    return device;
}

const VkQueue vk_device::get_graphics_queue() const 
{
    return graphics_queue;
}

const VkQueue vk_device::get_present_queue() const 
{
    return present_queue;
}

const vk_device::queue_family_indicies& vk_device::get_queue_family_indicies() const 
{
    return queue_indicies;
}

void vk_device::pick_physical_device(const VkInstance instance)
{
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
    if (device_count == 0)
    {
        _logger->fatal("Could not find a GPU with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

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

void vk_device::get_device_queue_indicies(const VkSurfaceKHR surface)
{
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, queue_families.data());

    for (size_t i = 0; i < queue_families.size(); ++i)
    {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            queue_indicies.graphics_family_index = i;
        }

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);
        if (present_support)
        {
            queue_indicies.present_family_index = i;
        }

        if (queue_families[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            queue_indicies.compute_family_index = i;
        }
    }
}

void vk_device::create_logical_device()
{
    std::set<uint32_t> unique_queue_indicies = {queue_indicies.graphics_family_index, queue_indicies.present_family_index};
    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    const float priority = 1.0f;
    for (uint32_t queue_index : unique_queue_indicies)
    {
        VkDeviceQueueCreateInfo queue_create_info{};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueCount = 1;
        queue_create_info.queueFamilyIndex = queue_index;
        queue_create_info.pQueuePriorities = &priority;
        queue_create_infos.push_back(queue_create_info);
    }

    VkDeviceCreateInfo device_create_info{};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
    device_create_info.pQueueCreateInfos = queue_create_infos.data();
    device_create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
    device_create_info.ppEnabledExtensionNames = device_extensions.data();

    VkPhysicalDeviceFeatures physical_device_features{};
    device_create_info.pEnabledFeatures = &physical_device_features;
    device_create_info.enabledLayerCount = 0;

    if (vkCreateDevice(physical_device, &device_create_info, nullptr, &device) != VK_SUCCESS)
    {
        _logger->error("Failed to create logical device");
    }

    /* grab the device queue handles for the graphics and present queues after logical device creation */
    vkGetDeviceQueue(device, queue_indicies.graphics_family_index, 0, &graphics_queue);
    vkGetDeviceQueue(device, queue_indicies.present_family_index, 0, &present_queue);
}