#include <limits>

#include "../../../inc/renderer/vulkan/vk_fence.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_fence;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_fence::vk_fence(const VkDevice device)
{
    VkFenceCreateInfo fence_create_info{};
    fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateFence(device, &fence_create_info, nullptr, &fence) != VK_SUCCESS)
    {
        _logger->error("Failed to create fence");
    }
}

const VkFence vk_fence::get_fence() const 
{
    return fence;
}

void vk_fence::block() const 
{
    vkWaitForFences(device, 1, &fence, VK_TRUE, std::numeric_limits<std::uint64_t>::max());
}

void vk_fence::reset() const 
{
    vkResetFences(device, 1, &fence);
}

vk_fence::~vk_fence()
{
    vkDestroyFence(device, fence, nullptr);
}