#ifndef VK_SEMAPHORE_H
#define VK_SEMAPHORE_H

#include <vulkan/vulkan.h>

namespace joszva::engine
{
    class vk_semaphore
    {
    public:
        vk_semaphore(const VkDevice device);
        ~vk_semaphore();

        const VkSemaphore get_semaphore() const;

    private:
        VkSemaphore semaphore;

        /* ref */
        VkDevice device;
    };
}
#endif