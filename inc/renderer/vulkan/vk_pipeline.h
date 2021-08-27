#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include <vector>
#include <vulkan/vulkan.h>

#include "vk_device.h"
#include "vk_swapchain.h"

namespace joszva::engine
{
    class vk_pipeline
    {
    public:
        vk_pipeline(const VkDevice device, const VkRenderPass render_pass, const VkExtent2D& swapchain_extent);
        ~vk_pipeline();

        const VkPipeline get_pipeline() const;
        const VkPipelineLayout get_pipeline_layout() const;

        void create_pipeline(const VkDevice device, const VkRenderPass render_pass, const VkExtent2D& swapchain_extent);

    private:
        VkShaderModule create_shader_module(const std::vector<char>& shader_code);

        VkPipeline pipeline;
        VkPipelineLayout pipeline_layout;

        /* ref */
        VkDevice device;
    };
}
#endif