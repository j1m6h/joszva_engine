#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer/vulkan/vk_descriptor_pool.h"
#include "renderer/vulkan/vk_device.h"
#include "renderer/vulkan/vk_instance.h"

#include "../vendor/joszva_graphics/inc/engine.h"

#include "../vendor/imgui/backends/imgui_impl_vulkan.h"

namespace joszva::engine
{
    class application
    {
    public:
        application();
        ~application();

        void run();

    private:
        void handle_events(window& win);
        void setup_vulkan_window(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);
        void cleanup_vulkan_window();
        void frame_render(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);
        void frame_present(ImGui_ImplVulkanH_Window* wd);
        void rebuild_swapchain();
        void cleanup();

        window win;
        /* wrapped vulkan objects */
        vk_instance _vk_instance;
        vk_device _vk_device;
        vk_descriptor_pool _vk_descriptor_pool;
        /*  */
        ImGui_ImplVulkanH_Window main_window_data;

        bool swap_chain_rebuild;
        bool on_closing;
    };
}
#endif