#ifndef VULKAN_IMPL_H
#define VULKAN_IMPL_H

#include "config.h"

#if defined(JOSZVA_SYS_LINUX)
    #include "../native/x11/vulkan_impl_x11.h"
#elif defined(JOSZVA_SYS_WINDOWS)
    #include "../native/win32/vulkan_impl_win32.h"
#endif

namespace joszva::graphics::priv
{
    namespace vulkan_impl
    {
    #if defined(JOSZVA_SYS_LINUX)
        using namespace vulkan_impl_x11;
    #elif defined(JOSZVA_SYS_WINDOWS)
        using namespace vulkan_impl_win32;
    #endif
    }
}
#endif