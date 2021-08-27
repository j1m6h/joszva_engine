#include <array>
#include <vulkan/vulkan.h>

#include "../../inc/renderer/renderer.h"

#include "../../vendor/imgui/backends/imgui_impl_vulkan.h"

#include "../../vendor/joszva_log/inc/logger.h"

using joszva::engine::renderer;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

renderer::~renderer()
{
}

void renderer::render_frame()
{
    vkWaitForFences(_vk_device->get_device(), 1, &in_flight_fences[current_frame], VK_TRUE, UINT64_MAX);

    uint32_t image_index;
    VkResult result = vkAcquireNextImageKHR(_vk_device->get_device(), _vk_swapchain->get_swapchain(),
        UINT64_MAX, image_available_semaphores[current_frame], VK_NULL_HANDLE, &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreate_swapchain();
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        _logger->error("Unable to acquire swapchain");
    }

    /* check if a previous frame is using this image */
    if (images_in_flight[image_index] != VK_NULL_HANDLE)
    {
        vkWaitForFences(_vk_device->get_device(), 1, &images_in_flight[image_index], VK_TRUE, UINT64_MAX);
    }

    images_in_flight[image_index] = in_flight_fences[current_frame];

    /* record UI draw data */
    record_ui_commands(image_index);

    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore wait_semaphores[] = {image_available_semaphores[current_frame]};
    VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    std::array<VkCommandBuffer, 2> cmd_buffers = {_vk_command_buffers->get_command_buffers()[image_index], _vk_command_buffers->get_imgui_command_buffers()[image_index]};
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = wait_semaphores;
    submit_info.pWaitDstStageMask = wait_stages;
    submit_info.commandBufferCount = static_cast<uint32_t>(cmd_buffers.size());
    submit_info.pCommandBuffers = cmd_buffers.data();

    VkSemaphore signal_semaphores[] = {render_finished_semaphores[current_frame]};
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = signal_semaphores;

    vkResetFences(_vk_device->get_device(), 1, &in_flight_fences[current_frame]);

    if (vkQueueSubmit(_vk_device->get_graphics_queue(), 1, &submit_info, in_flight_fences[current_frame]) != VK_SUCCESS)
    {
        _logger->error("Failed to submit draw command buffer");
    }

    VkPresentInfoKHR present_info{};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = signal_semaphores;

    VkSwapchainKHR swapchains[] = {_vk_swapchain->get_swapchain()};
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapchains;
    present_info.pImageIndices = &image_index;

    result = vkQueuePresentKHR(_vk_device->get_present_queue(), &present_info);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebuffer_resized)
    {
        framebuffer_resized = false;
        recreate_swapchain();
    }
    else if (result != VK_SUCCESS)
    {
        /* unable to present the swap chain image */
    }

    current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void renderer::recreate_swapchain()
{
    vkDeviceWaitIdle(_vk_device->get_device());

    /* cleanup previous resources */
    cleanup_swapchain();
    cleanup_imgui_resources();

    /* recreate needed resources */
    _vk_swapchain->create_swapchain(_vk_window_surface->get_surface());
    _vk_pipeline->create_pipeline(_vk_device->get_device(), _vk_swapchain->get_render_pass(), _vk_swapchain->get_swapchain_extent());
    _vk_descriptor_pool->create_descriptor_pool(*_vk_swapchain);
    _vk_command_buffers->create_command_buffers(*_vk_swapchain, _vk_pipeline->get_pipeline(), _vk_command_pool->get_command_pool());

    ImGui_ImplVulkan_SetMinImageCount(_vk_swapchain->get_image_count());
    _vk_command_buffers->create_imgui_command_buffers(*_vk_swapchain, _vk_command_pool->get_command_pool());
    _vk_swapchain->create_imgui_framebuffers();
}

void renderer::cleanup_swapchain()
{
    for (auto& framebuffer : _vk_swapchain->get_swapchain_framebuffers())
    {
        vkDestroyFramebuffer(_vk_device->get_device(), framebuffer, nullptr);
    }

    vkFreeCommandBuffers(_vk_device->get_device(), _vk_command_pool->get_command_pool(), 
        static_cast<uint32_t>(_vk_command_buffers->get_command_buffers().size()), _vk_command_buffers->get_command_buffers().data());

    vkDestroyPipeline(_vk_device->get_device(), _vk_pipeline->get_pipeline(), nullptr);
    vkDestroyPipelineLayout(_vk_device->get_device(), _vk_pipeline->get_pipeline_layout(), nullptr);
    vkDestroyRenderPass(_vk_device->get_device(), _vk_swapchain->get_render_pass(), nullptr);

    for (auto& image_view : _vk_swapchain->get_swapchain_image_views())
    {
        vkDestroyImageView(_vk_device->get_device(), image_view, nullptr);
    }

    vkDestroySwapchainKHR(_vk_device->get_device(), _vk_swapchain->get_swapchain(), nullptr);
}

void renderer::cleanup_imgui_resources()
{
    for (auto framebuffer : _vk_swapchain->get_imgui_framebuffers())
    {
        vkDestroyFramebuffer(_vk_device->get_device(), framebuffer, nullptr);
    }

    vkFreeCommandBuffers(_vk_device->get_device(), _vk_command_pool->get_imgui_command_pool(), 
        static_cast<uint32_t>(_vk_command_buffers->get_imgui_command_buffers().size()), _vk_command_buffers->get_imgui_command_buffers().data());
}