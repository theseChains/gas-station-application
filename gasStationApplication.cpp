#include "Application.h"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        Application app{};
        app.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Standart exception: " << exception.what() << '\n';
    }

    return 0;
}