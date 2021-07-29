#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include "config.h"

#if defined(JOSZVA_SYS_LINUX)
    #include "../native/x11/window_impl_x11.h"
#elif defined(JOSZVA_SYS_WINDOWS)
    #include "../native/win32/window_impl_win32.h"
#endif

namespace joszva::graphics::priv
{
#if defined(JOSZVA_SYS_LINUX)
    typedef window_impl_x11 window_impl;
#elif defined(JOSZVA_SYS_WINDOWS)
    typedef window_impl_win32 window_impl;
#endif
}
#endif