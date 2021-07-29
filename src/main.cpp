#include <chrono>
#include <iostream>
#include <thread>

#include "../vendor/graphics/inc/engine.h"

int main()
{
    window win("Joszva Engine", 600, 450);
    win.set_visible(true);

    /* handle the on close window event */
    win.on<close_event>([&win](const auto& event){
        win.destroy();
    });

    win.on<key_pressed_event>([](const auto& event){
        keyboard::key k = event.key;
        int k2 = reinterpret_cast<int>(k);
        std::cout << std::to_string(k2) << std::endl;
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