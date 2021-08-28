#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer/renderer.h"

#include "../vendor/joszva_graphics/inc/base/window.h"

namespace joszva::engine
{
    class application : public renderer
    {
    public:
        application(int argc, char** argv);
        ~application();

        void run();

    private:
        void handle_events();
        void init_renderer();
        void init_imgui();
        void draw_ui();

        void create_sync_objects();
        virtual void record_ui_commands(uint32_t buffer_index);

        void process_mouse_input();

        graphics::window win;
        bool is_closing;
    };
}
#endif