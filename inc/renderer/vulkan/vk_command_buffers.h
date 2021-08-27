#ifndef VK_COMMAND_BUFFERS_H
#define VK_COMMAND_BUFFERS_H

#include <vector>
#include <vulkan/vulkan.h>

#include "vk_swapchain.h"

namespace joszva::engine
{
    class vk_command_buffers
    {
    public:
        vk_command_buffers(const VkDevice device, const vk_swapchain& swapchain, const VkPipeline pipeline, const VkCommandPool command_pool);
        ~vk_command_buffers();

        const std::vector<VkCommandBuffer>& get_command_buffers() const;
        const std::vector<VkCommandBuffer>& get_imgui_command_buffers() const;

        void create_command_buffers(const vk_swapchain& swapchain, const VkPipeline pipeline, const VkCommandPool command_pool);
        /* create seperate command buffers for imgui */
        void create_imgui_command_buffers(const vk_swapchain& swapchain, const VkCommandPool imgui_command_pool);

    private:
        std::vector<VkCommandBuffer> command_buffers;
        std::vector<VkCommandBuffer> imgui_command_buffers;

        /* refs */
        VkDevice device;
        VkPipeline pipeline;
        VkCommandPool command_pool;
        VkCommandPool imgui_command_pool;
    };
}
#endif