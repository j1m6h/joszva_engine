#include <chrono>
#include <thread>

#include "../vendor/joszva_graphics/inc/engine.h"
#include "../vendor/joszva_log/inc/logger.h"

int main()
{
    window win("Joszva Engine", 600, 450);
    win.set_visible(true);

    /* handle the on close window event */
    win.on<close_event>([&win](const auto& event){
        win.destroy();
    });

    while (win.is_open())
    {
        win.process_events();

        /* update function here */
        /* temp */
        std::chrono::duration<double, std::milli> time(10);
        std::this_thread::sleep_for(time);
    }

    return 0;
}