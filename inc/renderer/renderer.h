#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "camera.h"

#include "vulkan/vk_command_buffers.h"
#include "vulkan/vk_command_pool.h"
#include "vulkan/vk_descriptor_pool.h"
#include "vulkan/vk_device.h"
#include "vulkan/vk_instance.h"
#include "vulkan/vk_pipeline.h"
#include "vulkan/vk_swapchain.h"
#include "vulkan/vk_window_surface.h"

namespace joszva::engine
{
    class renderer
    {
    public:
        renderer() = default;
        renderer(const renderer&) = delete;
        renderer(renderer&&) = delete;
        ~renderer();

        void render_frame();
        void recreate_swapchain();
        /* cleanup functions specifically for use when recreating the swapchain */
        void cleanup_swapchain();
        void cleanup_imgui_resources();
        /*  */
        virtual void record_ui_commands(uint32_t buffer_index) = 0;

        renderer& operator=(const renderer&) = delete;
        renderer& operator=(renderer&&) = delete;

    protected:
        std::unique_ptr<vk_instance> _vk_instance;
        std::unique_ptr<vk_window_surface> _vk_window_surface;
        std::unique_ptr<vk_device> _vk_device;
        std::unique_ptr<vk_swapchain> _vk_swapchain;
        std::unique_ptr<vk_pipeline> _vk_pipeline;
        std::unique_ptr<vk_command_pool> _vk_command_pool;
        std::unique_ptr<vk_command_buffers> _vk_command_buffers;
        std::unique_ptr<vk_descriptor_pool> _vk_descriptor_pool;

        std::unique_ptr<camera> _camera;

        std::vector<VkSemaphore> image_available_semaphores;
        std::vector<VkSemaphore> render_finished_semaphores;
        std::vector<VkFence> in_flight_fences;
        std::vector<VkFence> images_in_flight;

        uint32_t current_frame = 0;
        const uint32_t MAX_FRAMES_IN_FLIGHT = 2;
        bool framebuffer_resized = false;
        float time_passed{0.0f};
    };
}

#endif