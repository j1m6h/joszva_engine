#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <vulkan/vulkan.h>

#include "vk_instance.h"

namespace joszva::engine
{
    class vk_device
    {
    public:
        vk_device(const vk_instance& instance);
        ~vk_device();

        const VkDevice get_device() const;

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