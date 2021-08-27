#ifndef VK_DESCRIPTOR_POOL_H
#define VK_DESCRIPTOR_POOL_H

#include <vulkan/vulkan.h>

#include "vk_swapchain.h"

namespace joszva::engine
{
    class vk_descriptor_pool
    {
    public:
        vk_descriptor_pool(const VkDevice device, const vk_swapchain& swapchain);
        ~vk_descriptor_pool();

        const VkDescriptorPool get_descriptor_pool() const;
        const VkDescriptorPool get_imgui_descriptor_pool() const;
        
        void create_descriptor_pool(const vk_swapchain& swapchain);
        /* create a seperate descriptor pool for imgui */
        void create_imgui_descriptor_pool();

    private:
        VkDescriptorPool descriptor_pool;
        VkDescriptorPool imgui_descriptor_pool;

        /* ref */
        VkDevice device;
    };
}
#endif