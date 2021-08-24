#include <iostream>

#include "../inc/application.h"

int main()
{
    joszva::engine::application app;
    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}