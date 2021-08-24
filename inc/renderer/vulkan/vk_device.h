#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <vulkan/vulkan.h>

#include "vk_instance.h"

namespace joszva::engine
{
    class vk_device
    {
    public:
        vk_device();
        ~vk_device();

        const VkPhysicalDevice get_physical_device() const;
        const VkDevice get_device() const;
        const VkQueue get_queue() const;
        const uint32_t get_queue_family() const;
        void init(const vk_instance& instance);

    private:
        void pick_physical_device(const vk_instance& instance);
        void select_graphics_queue_family();
        void create_logical_device();

        VkPhysicalDevice physical_device;
        VkDevice device;
        VkQueue queue;
        uint32_t queue_family;
    };
}
#endif