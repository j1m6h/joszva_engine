#include "../../../inc/renderer/vulkan/vk_descriptor_pool.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_descriptor_pool;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_descriptor_pool::vk_descriptor_pool()
    : descriptor_pool(VK_NULL_HANDLE),
    device(VK_NULL_HANDLE)
{
}

vk_descriptor_pool::~vk_descriptor_pool()
{
    vkDestroyDescriptorPool(device, descriptor_pool, nullptr);
}

const VkDescriptorPool vk_descriptor_pool::get_descriptor_pool() const 
{
    return descriptor_pool;
}

void vk_descriptor_pool::init(const vk_device& device)
{
    this->device = device.get_device();
    create_descriptor_pool();
}

void vk_descriptor_pool::create_descriptor_pool()
{
    VkDescriptorPoolSize pool_sizes[] =
        {
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

    VkDescriptorPoolCreateInfo pool_info{};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 1000 * sizeof(pool_sizes);
    pool_info.poolSizeCount = static_cast<uint32_t>(sizeof(pool_sizes));
    pool_info.pPoolSizes = pool_sizes;
    if (vkCreateDescriptorPool(device, &pool_info, nullptr, &descriptor_pool) != VK_SUCCESS)
    {
        _logger->error("Failed to create descriptor pool");
        return;
    }

    _logger->info("Successfully created descriptor pool");
}