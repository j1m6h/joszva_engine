#include <limits>

#include "../../../inc/renderer/vulkan/vk_swapchain.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_swapchain;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_swapchain::vk_swapchain(const vk_device& device, const VkSurfaceKHR surface)
    : swapchain(VK_NULL_HANDLE),
    swapchain_extent({0, 0}),
    swapchain_image_format(),
    swapchain_images(0),
    swapchain_image_views(0),
    swapchain_framebuffers(0),
    image_count(2),
    render_pass(VK_NULL_HANDLE),
    device(device)
{
    create_swapchain(surface);
}

vk_swapchain::~vk_swapchain()
{
    /* this is done in the cleanup function, called on window close */
}

const VkSwapchainKHR vk_swapchain::get_swapchain() const 
{
    return swapchain;
}

const VkExtent2D vk_swapchain::get_swapchain_extent() const 
{
    return swapchain_extent;
}

const VkFormat& vk_swapchain::get_swapchain_image_format() const 
{
    return swapchain_image_format;
}

const std::vector<VkImage>& vk_swapchain::get_swapchain_images() const 
{
    return swapchain_images;
}

const std::vector<VkImageView>& vk_swapchain::get_swapchain_image_views() const 
{
    return swapchain_image_views;
}

const std::vector<VkFramebuffer>& vk_swapchain::get_swapchain_framebuffers() const 
{
    return swapchain_framebuffers;
}

const std::vector<VkFramebuffer>& vk_swapchain::get_imgui_framebuffers() const 
{
    return imgui_framebuffers;
}

const uint32_t vk_swapchain::get_image_count() const 
{
    return image_count;
}

const VkRenderPass vk_swapchain::get_render_pass() const 
{
    return render_pass;
}

const VkRenderPass vk_swapchain::get_imgui_render_pass() const 
{
    return imgui_render_pass;
}

void vk_swapchain::create_swapchain(const VkSurfaceKHR surface)
{
    swapchain_configuration config = query_swapchain_support(device.get_physical_device(), surface);

    VkSurfaceFormatKHR surface_format = pick_swapchain_surface_format(config.surface_formats);
    VkExtent2D extent = pick_swapchain_extent(config.capabilities);
    VkPresentModeKHR present_mode = pick_swapchain_present_mode(config.present_modes);

    image_count = config.capabilities.minImageCount + 1;
    if (config.capabilities.maxImageCount > 0 && image_count > config.capabilities.maxImageCount)
    {
        image_count = config.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR swapchain_create_info{};
    swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_create_info.surface = surface;
    swapchain_create_info.minImageCount = image_count;
    swapchain_create_info.imageFormat = surface_format.format;
    swapchain_create_info.imageColorSpace = surface_format.colorSpace;
    swapchain_create_info.imageExtent = extent;
    swapchain_create_info.imageArrayLayers = 1;
    swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t indicies[] = {device.get_queue_family_indicies().graphics_family_index, device.get_queue_family_indicies().present_family_index};
    if (device.get_queue_family_indicies().present_family_index == device.get_queue_family_indicies().graphics_family_index)
    {
        swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }
    else 
    {
        swapchain_create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_create_info.queueFamilyIndexCount = 2;
        swapchain_create_info.pQueueFamilyIndices = indicies;
    }

    swapchain_create_info.preTransform = config.capabilities.currentTransform;
    swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_create_info.presentMode = present_mode;
    swapchain_create_info.clipped = VK_TRUE;
    swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device.get_device(), &swapchain_create_info, nullptr, &swapchain) != VK_SUCCESS)
    {
        _logger->error("Failed to create swapchain");
    }

    swapchain_image_format = surface_format.format;
    swapchain_extent = extent;

    uint32_t swapchain_count;
    vkGetSwapchainImagesKHR(device.get_device(), swapchain, &swapchain_count, nullptr);
    swapchain_images.resize(swapchain_count);
    vkGetSwapchainImagesKHR(device.get_device(), swapchain, &swapchain_count, swapchain_images.data());

    create_image_views();
    create_render_pass();
    create_framebuffers();
}

void vk_swapchain::create_imgui_render_pass()
{
    VkAttachmentDescription attachment_desc{};
    attachment_desc.format = swapchain_image_format;
    attachment_desc.samples = VK_SAMPLE_COUNT_1_BIT;
    attachment_desc.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD; /* need ui to load on top of main */
    attachment_desc.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachment_desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; /* last pass so we want to present after */
    attachment_desc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachment_desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachment_desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    /* create color attachment reference */
    VkAttachmentReference attachment_ref{};
    attachment_ref.attachment = 0;
    attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    /* create subpass */
    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &attachment_ref;

    /* create subpass dependency to synchronize main and ui render passes */
    VkSubpassDependency subpass_dep{};
    subpass_dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpass_dep.dstSubpass = 0;
    subpass_dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpass_dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpass_dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpass_dep.dstStageMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    /* create ui render pass */
    VkRenderPassCreateInfo render_pass_create_info{};
    render_pass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_create_info.attachmentCount = 1;
    render_pass_create_info.pAttachments = &attachment_desc;
    render_pass_create_info.subpassCount = 1;
    render_pass_create_info.pSubpasses = &subpass;
    render_pass_create_info.dependencyCount = 1;
    render_pass_create_info.pDependencies = &subpass_dep;

    if (vkCreateRenderPass(device.get_device(), &render_pass_create_info, nullptr, &imgui_render_pass) != VK_SUCCESS) 
    {
        _logger->error("Failed to create IMGUI render pass");
    }
}

void vk_swapchain::create_imgui_framebuffers()
{
    imgui_framebuffers.resize(swapchain_images.size());
    VkImageView attachment[1];
    VkFramebufferCreateInfo framebuffer_create_info{};
    framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_create_info.renderPass = imgui_render_pass;
    framebuffer_create_info.attachmentCount = 1;
    framebuffer_create_info.pAttachments = attachment;
    framebuffer_create_info.width = swapchain_extent.width;
    framebuffer_create_info.height = swapchain_extent.height;
    framebuffer_create_info.layers = 1;
    for (uint32_t i = 0; i < swapchain_images.size(); ++i)
    {
        attachment[0] = swapchain_image_views[i];
        if (vkCreateFramebuffer(device.get_device(), &framebuffer_create_info, nullptr, &imgui_framebuffers[i]) != VK_SUCCESS)
        {
            _logger->error("Failed to create IMGUI framebuffers");
        }
    }
}

void vk_swapchain::cleanup()
{
    /* destroy image views */
    for (auto image_view : swapchain_image_views)
    {
        vkDestroyImageView(device.get_device(), image_view, nullptr);
    }

    /* destroy framebuffers */
    for (auto framebuffer : swapchain_framebuffers)
    {
        vkDestroyFramebuffer(device.get_device(), framebuffer, nullptr);
    }

    for (auto framebuffer : imgui_framebuffers)
    {
        vkDestroyFramebuffer(device.get_device(), framebuffer, nullptr);
    }

    /* destroy render passes */
    vkDestroyRenderPass(device.get_device(), render_pass, nullptr);
    vkDestroyRenderPass(device.get_device(), imgui_render_pass, nullptr);

    /* finally destroy the swapchain */
    /* this needs to be called before the render window is destroyed, otherwise we will get an access violation */
    vkDestroySwapchainKHR(device.get_device(), swapchain, nullptr);
}

void vk_swapchain::create_image_views()
{
    swapchain_image_views.resize(swapchain_images.size());
    for (size_t i = 0; i < swapchain_images.size(); ++i)
    {
        VkImageViewCreateInfo image_view_create_info{};
        image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_create_info.image = swapchain_images[i];
        image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_create_info.format = swapchain_image_format;
        image_view_create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_create_info.subresourceRange.baseArrayLayer = 0;
        image_view_create_info.subresourceRange.baseMipLevel = 0;
        image_view_create_info.subresourceRange.levelCount = 1;
        image_view_create_info.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device.get_device(), &image_view_create_info, nullptr, &swapchain_image_views[i]) != VK_SUCCESS)
        {
            _logger->error("Failed to create image views");
        }
    }
}

void vk_swapchain::create_render_pass()
{
    VkAttachmentDescription color_attachment{};
    color_attachment.format = swapchain_image_format;
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_attachment_ref{};
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass_description{};
    subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass_description.colorAttachmentCount = 1;
    subpass_description.pColorAttachments = &color_attachment_ref;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo render_pass_create_info{};
    render_pass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_create_info.attachmentCount = 1;
    render_pass_create_info.pAttachments = &color_attachment;
    render_pass_create_info.subpassCount = 1;
    render_pass_create_info.pSubpasses = &subpass_description;
    render_pass_create_info.dependencyCount = 1;
    render_pass_create_info.pDependencies = &dependency;

    if (vkCreateRenderPass(device.get_device(), &render_pass_create_info, nullptr, &render_pass) != VK_SUCCESS)
    {
        _logger->error("Failed to create render pass");
        return;
    }
}

void vk_swapchain::create_framebuffers()
{
    swapchain_framebuffers.resize(swapchain_image_views.size());
    for (size_t i = 0; i < swapchain_image_views.size(); ++i)
    {
        VkImageView attachments[] = {swapchain_image_views[i]};

        VkFramebufferCreateInfo framebuffer_create_info{};
        framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_create_info.renderPass = render_pass;
        framebuffer_create_info.attachmentCount = 1;
        framebuffer_create_info.pAttachments = attachments;
        framebuffer_create_info.width = swapchain_extent.width;
        framebuffer_create_info.height = swapchain_extent.height;
        framebuffer_create_info.layers = 1;

        if (vkCreateFramebuffer(device.get_device(), &framebuffer_create_info, nullptr, &swapchain_framebuffers[i]) != VK_SUCCESS)
        {
            _logger->error("Failed to create framebuffers");
        }
    }
}

vk_swapchain::swapchain_configuration vk_swapchain::query_swapchain_support(const VkPhysicalDevice& device, const VkSurfaceKHR surface)
{
    swapchain_configuration config{};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &config.capabilities);

    uint32_t format_count = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);
    if (format_count > 0)
    {
        config.surface_formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, config.surface_formats.data());
    }

    uint32_t present_mode_count = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);
    if (present_mode_count > 0)
    {
        config.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, config.present_modes.data());
    }

    return config;
}

VkSurfaceFormatKHR vk_swapchain::pick_swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& formats)
{
    for (VkSurfaceFormatKHR format : formats)
    {
        if (format.format == VK_FORMAT_B8G8R8_SRGB && format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
        {
            return format;
        }
    }

    return formats[0];
}

VkExtent2D vk_swapchain::pick_swapchain_extent(const VkSurfaceCapabilitiesKHR& surface_capabilities)
{
    if (surface_capabilities.currentExtent.width != UINT32_MAX)
    {
        return surface_capabilities.currentExtent;
    }
    else 
    {
        VkExtent2D actual_extent = {500, 400};
        actual_extent.width = std::max(surface_capabilities.minImageExtent.width, std::min(surface_capabilities.maxImageExtent.width, actual_extent.width));
        actual_extent.height = std::max(surface_capabilities.minImageExtent.height, std::min(surface_capabilities.maxImageExtent.height, actual_extent.height));
        return actual_extent;
    }
}

VkPresentModeKHR vk_swapchain::pick_swapchain_present_mode(const std::vector<VkPresentModeKHR>& present_modes)
{
    for (VkPresentModeKHR mode : present_modes)
    {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return mode;
        }
    }

    /* FIFO mode is the only gauranteed mode */
    return VK_PRESENT_MODE_FIFO_KHR;
}