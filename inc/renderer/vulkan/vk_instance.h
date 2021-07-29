#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include <vulkan/vulkan.h>

namespace joszva::engine
{
    /* a wrapper class for VkInstance */
    class vk_instance
    {
    public:
        vk_instance(const char** extensions, uint32_t extension_count);
        ~vk_instance();

    private:
        void create_instance(const char** extensions, uint32_t extension_count);
        void cleanup();

        VkInstance _vk_instance;
    };
}
#endif