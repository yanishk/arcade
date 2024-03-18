
#include "lib/IDisplayModule.hpp"
#include "core/Core.hpp"

int main(int ac, char **av)
{
    arcade::Core core;
    if (ac != 2)
        return 84;
    core.openLib(av[1]);
}