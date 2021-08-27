#ifndef VK_COMMAND_POOL_H
#define VK_COMMAND_POOL_H

#include <vulkan/vulkan.h>

#include "vk_device.h"

namespace joszva::engine
{
    class vk_command_pool
    {
    public:
        vk_command_pool(const vk_device& device);
        ~vk_command_pool();

        const VkCommandPool get_command_pool() const;
        const VkCommandPool get_imgui_command_pool() const;

        /* create seperate command pool for imgui */
        void create_imgui_command_pool();

    private:
        VkCommandPool command_pool;
        VkCommandPool imgui_command_pool;

        /* ref */
        const vk_device& device;
    };
}
#endif