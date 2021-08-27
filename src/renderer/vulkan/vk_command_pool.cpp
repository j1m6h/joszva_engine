#include "../../../inc/renderer/vulkan/vk_command_pool.h"

#include "../../../vendor/joszva_log/inc/logger.h"

using joszva::engine::vk_command_pool;

namespace 
{
    auto _logger = std::make_shared<joszva::logger>();
}

vk_command_pool::vk_command_pool(const vk_device& device)
    : command_pool(VK_NULL_HANDLE),
    device(device)
{
    VkCommandPoolCreateInfo command_pool_create_info{};
    command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_create_info.queueFamilyIndex = device.get_queue_family_indicies().graphics_family_index;

    if (vkCreateCommandPool(device.get_device(), &command_pool_create_info, nullptr, &command_pool) != VK_SUCCESS)
    {
        _logger->error("Failed to create command pool");
    }

    _logger->info("Successfully created command pool");
}

vk_command_pool::~vk_command_pool()
{
    vkDestroyCommandPool(device.get_device(), command_pool, nullptr);
    vkDestroyCommandPool(device.get_device(), imgui_command_pool, nullptr);
}

const VkCommandPool vk_command_pool::get_command_pool() const 
{
    return command_pool;
}

const VkCommandPool vk_command_pool::get_imgui_command_pool() const 
{
    return imgui_command_pool;
}

void vk_command_pool::create_imgui_command_pool()
{
    VkCommandPoolCreateInfo command_pool_create_info{};
    command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_create_info.queueFamilyIndex = device.get_queue_family_indicies().graphics_family_index;
    command_pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(device.get_device(), &command_pool_create_info, nullptr, &imgui_command_pool) != VK_SUCCESS)
    {
        _logger->error("Failed to create IMGUI command pool");
    }
}