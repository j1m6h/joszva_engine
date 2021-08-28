#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <array>
#include <vulkan/vulkan.h>

namespace joszva::engine
{
    /* a wrapper for our physical device, logical device, and device queues */
    class vk_device
    {
    private:
        struct queue_family_indicies
        {
            uint32_t graphics_family_index;
            uint32_t compute_family_index;
            uint32_t present_family_index;
        };

    public:
        vk_device(const VkInstance instance, const VkSurfaceKHR surface);
        ~vk_device();

        const VkPhysicalDevice get_physical_device() const;
        const VkDevice get_device() const;
        const VkQueue get_graphics_queue() const;
        const VkQueue get_present_queue() const;
        const queue_family_indicies& get_queue_family_indicies() const;

    private:
        void pick_physical_device(const VkInstance instance);
        void get_device_queue_indicies(const VkSurfaceKHR surface);
        void create_logical_device();

        VkPhysicalDevice physical_device;
        VkDevice device;
        
        VkQueue graphics_queue;
        VkQueue present_queue;
        queue_family_indicies queue_indicies;

        const std::array<const char*, 1> device_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
    };
}
#endif