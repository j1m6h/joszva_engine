#include "imgui_impl_joszva.h"

#include "../../joszva_graphics/inc/base/keyboard.h"

namespace
{
    window& _win;
}

static bool imgui_impl_joszva_init(const window& win, bool install_callbacks)
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendPlatformUserData == NULL && "Already initialized a platform backend!");

    io.KeyMap[ImGuiKey_Tab] = static_cast<int>(joszva::graphics::keyboard::key::TAB);

    _win = win;
}

static void imgui_impl_joszva_update_mouse_pos_and_buttons()
{
    ImGuiIO& io = ImGui::GetIO();

    const ImVec2 mouse_pos_prev = io.MousePos;
    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
}

void imgui_impl_joszva_new_frame()
{
    ImGuiIO& io = ImGui::GetIO();

    int width = _win.get_size().x;
    int height = _win.get_size().y;
    int display_width = width;
    int display_height = height;
    io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));

    if (width > 0 && height > 0)
    {
        io.DisplayFramebufferScale = ImVec2(static_cast<float>(display_width / width), static_cast<float>(display_height / height));
    }

    imgui_impl_joszva_update_mouse_pos_and_buttons();
}