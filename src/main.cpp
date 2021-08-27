#include <iostream>

#include "../inc/application.h"

int main(int argc, char* argv[])
{
    joszva::engine::application app(argc, argv);
    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}