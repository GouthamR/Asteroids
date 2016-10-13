#include <iostream>
#include <stdexcept>

#include "game.h"

int main()
{
    try
    {
        Game game;
        game.run();
        return 0;
    }
    catch(std::runtime_error &e)
    {
        std::cout << "ERROR:" << std::endl;
        std::cout << e.what() << std::endl;
        return -1;
    }
}
