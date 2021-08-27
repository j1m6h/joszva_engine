#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include <vector>
#include <vulkan/vulkan.h>

#include "vk_device.h"

namespace joszva::engine
{
    class vk_swapchain
    {
    public:
        vk_swapchain(const vk_device& device, const VkSurfaceKHR surface);
        ~vk_swapchain();

        struct swapchain_configuration
        {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> surface_formats;
            std::vector<VkPresentModeKHR> present_modes;
        };

        const VkSwapchainKHR get_swapchain() const;
        const VkExtent2D get_swapchain_extent() const;
        const VkFormat& get_swapchain_image_format() const;
        const std::vector<VkImage>& get_swapchain_images() const;
        const std::vector<VkImageView>& get_swapchain_image_views() const;
        const std::vector<VkFramebuffer>& get_swapchain_framebuffers() const;
        const std::vector<VkFramebuffer>& get_imgui_framebuffers() const;
        const uint32_t get_image_count() const;
        const VkRenderPass get_render_pass() const;
        const VkRenderPass get_imgui_render_pass() const;

        void create_swapchain(const VkSurfaceKHR surface);

        /* create a seperate render pass, and seperate framebuffers for our imgui overlay */
        void create_imgui_render_pass();
        void create_imgui_framebuffers();
        /* cleanup swapchain */
        void cleanup();

    private:
        void create_image_views();
        void create_render_pass();
        void create_framebuffers();

        swapchain_configuration query_swapchain_support(const VkPhysicalDevice& device, const VkSurfaceKHR surface);
        VkSurfaceFormatKHR pick_swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& formats);
        VkExtent2D pick_swapchain_extent(const VkSurfaceCapabilitiesKHR& surface_capabilities);
        VkPresentModeKHR pick_swapchain_present_mode(const std::vector<VkPresentModeKHR>& present_modes);

        VkSwapchainKHR swapchain;
        VkExtent2D swapchain_extent;
        VkFormat swapchain_image_format;
        std::vector<VkImage> swapchain_images;
        std::vector<VkImageView> swapchain_image_views;
        std::vector<VkFramebuffer> swapchain_framebuffers;
        std::vector<VkFramebuffer> imgui_framebuffers;
        uint32_t image_count;

        VkRenderPass render_pass;
        VkRenderPass imgui_render_pass;

        const vk_device& device;
    };
}
#endif