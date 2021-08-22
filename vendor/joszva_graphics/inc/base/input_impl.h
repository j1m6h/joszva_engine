#ifndef INPUT_IMPL_H
#define INPUT_IMPL_H

#include "config.h"

#if defined(JOSZVA_SYS_LINUX)
    #include "../native/x11/input_impl_x11.h"
#elif defined(JOSZVA_SYS_WINDOWS)
    #include "../native/win32/input_impl_win32.h"
#endif

namespace joszva::graphics::priv
{
    namespace input_impl
    {
    #if defined(JOSZVA_SYS_LINUX)
        using namespace input_impl_x11;
    #elif defined(JOSZVA_SYS_WINDOWS)
        using namespace input_impl_win32;
    #endif
    }
}
#endif