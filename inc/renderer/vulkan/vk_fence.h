#ifndef VK_FENCE_H
#define VK_FENCE_H

#include <vulkan/vulkan.h>

#include "vk_device.h"

namespace joszva::engine
{
    class vk_fence
    {
    public:
        vk_fence(const VkDevice device);
        ~vk_fence();

        const VkFence get_fence() const;
        void block() const;
        void reset() const;

    private:
        VkFence fence;

        /* ref */
        VkDevice device;
    };
}
#endif