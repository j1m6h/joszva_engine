#include "../../../inc/renderer/vulkan/vk_command_buffers.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_command_buffers;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_command_buffers::vk_command_buffers(const VkDevice device, const vk_swapchain& swapchain, const VkPipeline pipeline, const VkCommandPool command_pool)
    : command_buffers(0),
    device(device),
    pipeline(pipeline),
    command_pool(command_pool)
{
    create_command_buffers(swapchain, pipeline, command_pool);
}

vk_command_buffers::~vk_command_buffers()
{
    vkFreeCommandBuffers(device, command_pool, static_cast<uint32_t>(command_buffers.size()), command_buffers.data());
    vkFreeCommandBuffers(device, imgui_command_pool, static_cast<uint32_t>(imgui_command_buffers.size()), imgui_command_buffers.data());
}

const std::vector<VkCommandBuffer>& vk_command_buffers::get_command_buffers() const
{
    return command_buffers;
}

const std::vector<VkCommandBuffer>& vk_command_buffers::get_imgui_command_buffers() const 
{
    return imgui_command_buffers;
}

void vk_command_buffers::create_command_buffers(const vk_swapchain& swapchain, const VkPipeline pipeline, const VkCommandPool command_pool)
{
    command_buffers.resize(swapchain.get_swapchain_framebuffers().size());

    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool = command_pool;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

    if (vkAllocateCommandBuffers(device, &alloc_info, command_buffers.data()) != VK_SUCCESS)
    {
        _logger->error("Failed to record command buffers");
    }

    for (size_t i = 0; i < command_buffers.size(); ++i)
    {
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(command_buffers[i], &begin_info) != VK_SUCCESS)
        {
            _logger->error("Failed to begin recording command buffers");
        }

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = swapchain.get_render_pass();
        render_pass_info.framebuffer = swapchain.get_swapchain_framebuffers()[i];
        render_pass_info.renderArea.offset = {0, 0};
        render_pass_info.renderArea.extent = swapchain.get_swapchain_extent();

        // Set the clear color value to black
        VkClearValue clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
        render_pass_info.clearValueCount = 1;
        render_pass_info.pClearValues = &clear_color;

        vkCmdBeginRenderPass(command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        vkCmdDraw(command_buffers[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(command_buffers[i]);

        if (vkEndCommandBuffer(command_buffers[i]) != VK_SUCCESS)
        {
            _logger->error("Failed to record command buffers");
        }
    }
}

void vk_command_buffers::create_imgui_command_buffers(const vk_swapchain& swapchain, const VkCommandPool imgui_command_pool)
{
    this->imgui_command_pool = imgui_command_pool;
    imgui_command_buffers.resize(swapchain.get_swapchain_image_views().size());

    VkCommandBufferAllocateInfo cmd_buffer_alloc_info{};
    cmd_buffer_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_buffer_alloc_info.commandPool = imgui_command_pool;
    cmd_buffer_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_buffer_alloc_info.commandBufferCount = static_cast<uint32_t>(imgui_command_buffers.size());

    if (vkAllocateCommandBuffers(device, &cmd_buffer_alloc_info, imgui_command_buffers.data()) != VK_SUCCESS)
    {
        _logger->error("Failed to create IMGUI command buffers");
    }
}