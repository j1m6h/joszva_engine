#include "../inc/application.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_joszva.h"
#include "../vendor/imgui/backends/imgui_impl_vulkan.h"

#include "../vendor/joszva_graphics/inc/base/event_system/event_types.h"

#include "../vendor/joszva_log/inc/logger.h"

using joszva::engine::application;

application::application(int argc, char** argv)
    : win("Test", 700, 555),
    is_closing(false)
{
    init_renderer();
    init_imgui();

    win.set_visible(true);
}

application::~application()
{
}

void application::handle_events()
{
    win.on<graphics::close_event>([this](const auto& event){
        is_closing = true;
        _vk_swapchain->cleanup();
        win.destroy();
    });
}

void application::init_renderer()
{
    _vk_instance = std::make_unique<vk_instance>();
    _vk_window_surface = std::make_unique<vk_window_surface>(_vk_instance->get_instance(), win);
    _vk_device = std::make_unique<vk_device>(_vk_instance->get_instance(), _vk_window_surface->get_surface());
    _vk_swapchain = std::make_unique<vk_swapchain>(*_vk_device, _vk_window_surface->get_surface());
    _vk_pipeline = std::make_unique<vk_pipeline>(_vk_device->get_device(), _vk_swapchain->get_render_pass(), _vk_swapchain->get_swapchain_extent());
    _vk_command_pool = std::make_unique<vk_command_pool>(*_vk_device);
    _vk_command_buffers = std::make_unique<vk_command_buffers>(_vk_device->get_device(), *_vk_swapchain, _vk_pipeline->get_pipeline(), _vk_command_pool->get_command_pool());
    _vk_descriptor_pool = std::make_unique<vk_descriptor_pool>(_vk_device->get_device(), *_vk_swapchain);
    create_sync_objects();
}

static VkCommandBuffer begin_single_time_commands(const VkDevice device, const VkCommandPool cmd_pool)
{
    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandPool = cmd_pool;
    alloc_info.commandBufferCount = 1;

    VkCommandBuffer command_buffer{};
    vkAllocateCommandBuffers(device, &alloc_info, &command_buffer);

    VkCommandBufferBeginInfo begin_info{};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if (vkBeginCommandBuffer(command_buffer, &begin_info) != VK_SUCCESS)
    {
    }

    return command_buffer;
}

static void end_single_time_commands(const joszva::engine::vk_device& device, const VkCommandBuffer cmd_buffer, const VkCommandPool cmd_pool)
{
    vkEndCommandBuffer(cmd_buffer);

    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &cmd_buffer;

    vkQueueSubmit(device.get_graphics_queue(), 1, &submit_info, VK_NULL_HANDLE);
    vkQueueWaitIdle(device.get_graphics_queue());

    vkFreeCommandBuffers(device.get_device(), cmd_pool, 1, &cmd_buffer);
}

void application::init_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    _vk_descriptor_pool->create_imgui_descriptor_pool();
    _vk_swapchain->create_imgui_render_pass();
    _vk_command_pool->create_imgui_command_pool();
    _vk_command_buffers->create_imgui_command_buffers(*_vk_swapchain, _vk_command_pool->get_imgui_command_pool());
    _vk_swapchain->create_imgui_framebuffers();

    imgui_impl_joszva_init_for_vulkan(win, true);
    ImGui_ImplVulkan_InitInfo init_info{};
    init_info.Instance = _vk_instance->get_instance();
    init_info.PhysicalDevice = _vk_device->get_physical_device();
    init_info.Device = _vk_device->get_device();
    init_info.QueueFamily = _vk_device->get_queue_family_indicies().graphics_family_index;
    init_info.Queue = _vk_device->get_graphics_queue();
    init_info.DescriptorPool = _vk_descriptor_pool->get_imgui_descriptor_pool();
    init_info.MinImageCount = _vk_swapchain->get_image_count();
    init_info.ImageCount = _vk_swapchain->get_image_count();
    ImGui_ImplVulkan_Init(&init_info, _vk_swapchain->get_imgui_render_pass());

    VkCommandBuffer command_buffer = begin_single_time_commands(_vk_device->get_device(), _vk_command_pool->get_imgui_command_pool());
    ImGui_ImplVulkan_CreateFontsTexture(command_buffer);
    end_single_time_commands(*_vk_device, command_buffer, _vk_command_pool->get_imgui_command_pool());
    ImGui_ImplVulkan_DestroyFontUploadObjects();
}

void application::draw_ui()
{
    ImGui_ImplVulkan_NewFrame();
    imgui_impl_joszva_new_frame(win);
    ImGui::NewFrame();

    ImGui::Begin("Test window");
    std::string fps = std::to_string(current_frame);
    ImGui::Text(fps.c_str());
    ImGui::End();

    ImGui::Render();
}

void application::run()
{
    handle_events();
    while (win.is_open())
    {
        win.process_events();

        if (!is_closing)
        {
            draw_ui();
            render_frame();
        }
    }

    vkDeviceWaitIdle(_vk_device->get_device());
}

void application::create_sync_objects()
{
    image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);
    images_in_flight.resize(_vk_swapchain->get_swapchain_images().size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphore_create_info{};
    semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_create_info{};
    fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        if (vkCreateSemaphore(_vk_device->get_device(), &semaphore_create_info, nullptr, &image_available_semaphores[i]) != VK_SUCCESS)
        {
        }

        if (vkCreateSemaphore(_vk_device->get_device(), &semaphore_create_info, nullptr, &render_finished_semaphores[i]) != VK_SUCCESS)
        {
        }

        if (vkCreateFence(_vk_device->get_device(), &fence_create_info, nullptr, &in_flight_fences[i]) != VK_SUCCESS)
        {

        }
    }
}

void application::record_ui_commands(uint32_t buffer_index)
{
    VkCommandBufferBeginInfo cmdBufferBegin = {};
    cmdBufferBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBufferBegin.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if (vkBeginCommandBuffer(_vk_command_buffers->get_imgui_command_buffers()[buffer_index], &cmdBufferBegin) != VK_SUCCESS) 
    {
        throw std::runtime_error("Unable to start recording UI command buffer!");
    }

    VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = _vk_swapchain->get_imgui_render_pass();
    renderPassBeginInfo.framebuffer = _vk_swapchain->get_imgui_framebuffers()[buffer_index];
    renderPassBeginInfo.renderArea.extent.width = _vk_swapchain->get_swapchain_extent().width;
    renderPassBeginInfo.renderArea.extent.height = _vk_swapchain->get_swapchain_extent().height;
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(_vk_command_buffers->get_imgui_command_buffers()[buffer_index], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Grab and record the draw data for Dear Imgui
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), _vk_command_buffers->get_imgui_command_buffers()[buffer_index]);

    // End and submit render pass
    vkCmdEndRenderPass(_vk_command_buffers->get_imgui_command_buffers()[buffer_index]);

    if (vkEndCommandBuffer(_vk_command_buffers->get_imgui_command_buffers()[buffer_index]) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to record command buffers!");
    }
}