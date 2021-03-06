#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include <vulkan/vulkan.h>

namespace joszva::engine
{
    /* a wrapper class for VkInstance */
    class vk_instance
    {
    public:
        vk_instance();
        ~vk_instance();

        const VkInstance get_instance() const;

    private:
        VkInstance instance;
    };
}
#endif