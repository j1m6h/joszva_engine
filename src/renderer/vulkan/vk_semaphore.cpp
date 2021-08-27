#include "../../../inc/renderer/vulkan/vk_semaphore.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_semaphore;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_semaphore::vk_semaphore(const VkDevice device)
{
    VkSemaphoreCreateInfo semaphore_create_info{};
    semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(device, &semaphore_create_info, nullptr, &semaphore) != VK_SUCCESS)
    {
        _logger->error("Failed to create semaphore");
    }
}

const VkSemaphore vk_semaphore::get_semaphore() const 
{
    return semaphore;
}

vk_semaphore::~vk_semaphore()
{
    vkDestroySemaphore(device, semaphore, nullptr);
}