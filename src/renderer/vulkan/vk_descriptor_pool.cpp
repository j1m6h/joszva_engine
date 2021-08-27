#include "../../../inc/renderer/vulkan/vk_descriptor_pool.h"

#include "../../../vendor/imgui/imgui.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_descriptor_pool;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_descriptor_pool::vk_descriptor_pool(const VkDevice device, const vk_swapchain& swapchain)
    : descriptor_pool(VK_NULL_HANDLE),
    device(device)
{
    create_descriptor_pool(swapchain);
}

vk_descriptor_pool::~vk_descriptor_pool()
{
    vkDestroyDescriptorPool(device, descriptor_pool, nullptr);
    vkDestroyDescriptorPool(device, imgui_descriptor_pool, nullptr);
}

const VkDescriptorPool vk_descriptor_pool::get_descriptor_pool() const 
{
    return descriptor_pool;
}

const VkDescriptorPool vk_descriptor_pool::get_imgui_descriptor_pool() const 
{
    return imgui_descriptor_pool;
}

void vk_descriptor_pool::create_descriptor_pool(const vk_swapchain& swapchain)
{
    VkDescriptorPoolSize pool_size{};
    pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    pool_size.descriptorCount = static_cast<uint32_t>(swapchain.get_swapchain_images().size());

    VkDescriptorPoolCreateInfo pool_create_info{};
    pool_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_create_info.maxSets = static_cast<uint32_t>(swapchain.get_swapchain_images().size());
    pool_create_info.poolSizeCount = 1;
    pool_create_info.pPoolSizes = &pool_size;

    if (vkCreateDescriptorPool(device, &pool_create_info, nullptr, &descriptor_pool) != VK_SUCCESS)
    {
        _logger->error("Failed to create descriptor pool");
    }
}

void vk_descriptor_pool::create_imgui_descriptor_pool()
{
    VkDescriptorPoolSize pool_sizes[] = {
        {VK_DESCRIPTOR_TYPE_SAMPLER, 1000},
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
        {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000},
        {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
        {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000}
    };

    VkDescriptorPoolCreateInfo pool_create_info{};
    pool_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_create_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_create_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
    pool_create_info.poolSizeCount = static_cast<uint32_t>(IM_ARRAYSIZE(pool_sizes));
    pool_create_info.pPoolSizes = pool_sizes;
    if (vkCreateDescriptorPool(device, &pool_create_info, nullptr, &imgui_descriptor_pool) != VK_SUCCESS)
    {
        _logger->error("Failed to create IMGUI descriptor pool");
    }
}