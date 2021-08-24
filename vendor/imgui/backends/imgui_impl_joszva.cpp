#include "imgui_impl_joszva.h"

#include "../../joszva_graphics/inc/base/keyboard.h"
#include "../../joszva_graphics/inc/base/mouse.h"

using namespace joszva::graphics::keyboard;
using namespace joszva::graphics::mouse;

static bool imgui_impl_joszva_init(const window& win, bool install_callbacks)
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendPlatformUserData == NULL && "Already initialized a platform backend!");

    io.BackendPlatformName = "imgui_impl_joszva";

    return true;
}

static void imgui_impl_joszva_update_mouse_pos_and_buttons(const window& win)
{
    ImGuiIO& io = ImGui::GetIO();

    int x = win.get_cursor_coords().x;
    int y = win.get_cursor_coords().y;
    io.MousePos = ImVec2(x, y);

    io.MouseDown[0] = joszva::graphics::mouse::is_mouse_pressed(joszva::graphics::mouse::button::LEFT);
}

bool imgui_impl_joszva_init_for_vulkan(const window& win, bool install_callbacks)
{
    return imgui_impl_joszva_init(win, install_callbacks);
}

void imgui_impl_joszva_new_frame(const window& win)
{
    ImGuiIO& io = ImGui::GetIO();

    int width = win.get_size().x;
    int height = win.get_size().y;
    int display_width = width;
    int display_height = height;
    io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));

    if (width > 0 && height > 0)
    {
        io.DisplayFramebufferScale = ImVec2(static_cast<float>(display_width / width), static_cast<float>(display_height / height));
    }

    imgui_impl_joszva_update_mouse_pos_and_buttons(win);
}

void imgui_impl_joszva_shutdown()
{
    ImGuiIO& io = ImGui::GetIO();

    io.BackendPlatformName = nullptr;
}