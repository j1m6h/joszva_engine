#include "../inc/application.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_joszva.h"

#include "../vendor/joszva_log/inc/logger.h"

using joszva::engine::application;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

application::application()
    : win("Joszva Window", 800, 500),
    _vk_instance(vk_instance()),
    _vk_device(vk_device()),
    _vk_descriptor_pool(vk_descriptor_pool()),
    main_window_data(ImGui_ImplVulkanH_Window()),
    swap_chain_rebuild(false),
    on_closing(false)
{
    /* initialize our vulkan object wrappers */
    uint32_t extension_count = 0;
    const char** extensions = win.get_required_instance_extensions(&extension_count);
    _vk_instance.init(extensions, extension_count);
    _vk_device.init(_vk_instance);
    _vk_descriptor_pool.init(_vk_device);

    win.set_visible(true);
}

application::~application()
{
}

void application::handle_events(window& win)
{
    win.on<close_event>([this](const auto& event){
        cleanup();
    });
}

#include <string>
void application::run()
{
    VkSurfaceKHR surface;
    win.create_vulkan_surface(_vk_instance.get_instance(), nullptr, surface);

    /* create framebuffers */
    int w = win.get_size().x;
    int h = win.get_size().y;
    ImGui_ImplVulkanH_Window* wd = &main_window_data;
    setup_vulkan_window(wd, surface, w, h);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    imgui_impl_joszva_init_for_vulkan(win, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = _vk_instance.get_instance();
    init_info.PhysicalDevice = _vk_device.get_physical_device();
    init_info.Device = _vk_device.get_device();
    init_info.QueueFamily = _vk_device.get_queue_family();
    init_info.Queue = _vk_device.get_queue();
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.DescriptorPool = _vk_descriptor_pool.get_descriptor_pool();
    init_info.Allocator = nullptr;
    init_info.MinImageCount = 2;
    init_info.ImageCount = wd->ImageCount;
    init_info.CheckVkResultFn = nullptr;
    ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);

     // Upload Fonts
    {
        // Use any command queue
        VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
        VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

        vkResetCommandPool(_vk_device.get_device(), command_pool, 0);
        VkCommandBufferBeginInfo begin_info = {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(command_buffer, &begin_info);

        ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

        VkSubmitInfo end_info = {};
        end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        end_info.commandBufferCount = 1;
        end_info.pCommandBuffers = &command_buffer;
        vkEndCommandBuffer(command_buffer);
        vkQueueSubmit(_vk_device.get_queue(), 1, &end_info, VK_NULL_HANDLE);

        vkDeviceWaitIdle(_vk_device.get_device());
        ImGui_ImplVulkan_DestroyFontUploadObjects();
    }

    handle_events(win);

    while (win.is_open())
    {
        win.process_events();

        /* if the application is not in the process of exiting */
        if (!on_closing)
        {
            if (swap_chain_rebuild)
            {
                _logger->warning("Rebuilding swapchain...");
                rebuild_swapchain();
                _logger->info("Swapchain rebuilt!");
            }

            ImGui_ImplVulkan_NewFrame();
            imgui_impl_joszva_new_frame(win);
            ImGui::NewFrame();

            {
                ImGui::Begin("Joszva debugga");
                ImGui::Button("Button box");

                std::string text = "Cursor Coords : " + std::to_string(win.get_cursor_coords().x) + ", " + std::to_string(win.get_cursor_coords().y);
                ImGui::Text(text.c_str());
                ImGui::End();
            }

            ImGui::Render();
            ImDrawData *draw_data = ImGui::GetDrawData();
            const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
            if (!is_minimized)
            {
                frame_render(wd, draw_data);
                frame_present(wd);
            }
        }
    }
}

void application::setup_vulkan_window(ImGui_ImplVulkanH_Window *wd, VkSurfaceKHR surface, int width, int height)
{
    wd->Surface = surface;

    // check for WSI support
    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(_vk_device.get_physical_device(), 
        _vk_device.get_queue_family(), wd->Surface, &res);
    if (res != VK_TRUE)
    {
        _logger->warning("WSI is not supported...");
    }

    /* select surface format */
    const VkFormat requestSurfaceImageFormat[] = {VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM};
    const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(_vk_device.get_physical_device(),
         wd->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

    /* select preset mode */
#ifdef IMGUI_UNLIMITED_FRAME_RATE
    VkPresentModeKHR present_modes[] = {VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR};
#else
    VkPresentModeKHR present_modes[] = {VK_PRESENT_MODE_FIFO_KHR};
#endif
    wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(_vk_device.get_physical_device(), wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));

    /* create swapchain, renderpass, framebuffer, etc. */
    ImGui_ImplVulkanH_CreateOrResizeWindow(_vk_instance.get_instance(),
         _vk_device.get_physical_device(), _vk_device.get_device(), wd, _vk_device.get_queue_family(),
         nullptr, width, height, 2);
}

void application::cleanup_vulkan_window()
{
    ImGui_ImplVulkanH_DestroyWindow(_vk_instance.get_instance(), _vk_device.get_device(), &main_window_data, nullptr);
}

void application::frame_render(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data)
{
    VkResult err;

    VkSemaphore image_acquired_semaphore  = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    err = vkAcquireNextImageKHR(_vk_device.get_device(), wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    {
        swap_chain_rebuild = true;
        return;
    }

    ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
    {
        err = vkWaitForFences(_vk_device.get_device(), 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking

        err = vkResetFences(_vk_device.get_device(), 1, &fd->Fence);
    }
    {
        err = vkResetCommandPool(_vk_device.get_device(), fd->CommandPool, 0);
        VkCommandBufferBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
    }
    {
        VkRenderPassBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        info.renderPass = wd->RenderPass;
        info.framebuffer = fd->Framebuffer;
        info.renderArea.extent.width = wd->Width;
        info.renderArea.extent.height = wd->Height;
        info.clearValueCount = 1;
        info.pClearValues = &wd->ClearValue;
        vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
    }

    // Record dear imgui primitives into command buffer
    ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

    // Submit command buffer
    vkCmdEndRenderPass(fd->CommandBuffer);
    {
        VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        VkSubmitInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &image_acquired_semaphore;
        info.pWaitDstStageMask = &wait_stage;
        info.commandBufferCount = 1;
        info.pCommandBuffers = &fd->CommandBuffer;
        info.signalSemaphoreCount = 1;
        info.pSignalSemaphores = &render_complete_semaphore;

        err = vkEndCommandBuffer(fd->CommandBuffer);
        err = vkQueueSubmit(_vk_device.get_queue(), 1, &info, fd->Fence);
    }
}

void application::frame_present(ImGui_ImplVulkanH_Window* wd)
{
    if (swap_chain_rebuild)
        return;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    VkPresentInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &render_complete_semaphore;
    info.swapchainCount = 1;
    info.pSwapchains = &wd->Swapchain;
    info.pImageIndices = &wd->FrameIndex;
    VkResult err = vkQueuePresentKHR(_vk_device.get_queue(), &info);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    {
        _logger->warning("Swapchain needs to be rebuilt!");
        swap_chain_rebuild = true;
        return;
    }

    wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->ImageCount; // Now we can use the next set of semaphores
}

void application::rebuild_swapchain()
{
    int width = win.get_size().x;
    int height = win.get_size().y;
    if (width > 0 && height > 0)
    {
        ImGui_ImplVulkan_SetMinImageCount(2);
        ImGui_ImplVulkanH_CreateOrResizeWindow(_vk_instance.get_instance(), _vk_device.get_physical_device(),
            _vk_device.get_device(), &main_window_data, _vk_device.get_queue_family(), nullptr, width, height, 2);
        main_window_data.FrameIndex = 0;
        swap_chain_rebuild = false;
    }
}

void application::cleanup()
{
    on_closing = true;
    vkDeviceWaitIdle(_vk_device.get_device());
    ImGui_ImplVulkan_Shutdown();
    imgui_impl_joszva_shutdown();
    ImGui::DestroyContext();

    cleanup_vulkan_window();
    win.destroy();
}