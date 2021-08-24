#ifndef IMGUI_IMPL_JOSZVA_H
#define IMGUI_IMPL_JOSZVA_H

#include "../imgui.h"
#include "../../joszva_graphics/inc/base/window.h"

using joszva::graphics::window;

IMGUI_IMPL_API bool imgui_impl_joszva_init_for_vulkan(const window& win, bool install_callbacks);
IMGUI_IMPL_API void imgui_impl_joszva_new_frame(const window& win);
IMGUI_IMPL_API void imgui_impl_joszva_shutdown();

#endif