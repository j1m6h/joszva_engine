#ifndef VK_DESCRIPTOR_POOL_H
#define VK_DESCRIPTOR_POOL_H

#include <vulkan/vulkan.h>

#include "vk_device.h"

namespace joszva::engine
{
    class vk_descriptor_pool
    {
    public:
        vk_descriptor_pool(const vk_device& device);
        ~vk_descriptor_pool();

    private:
        void create_descriptor_pool();

        VkDescriptorPool descriptor_pool;
        VkDevice device;
    };
}
#endif