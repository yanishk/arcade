
#include "lib/IDisplayModule.hpp"
#include "core/Core.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;
    arcade::Core core(av[1], av[2]);
    core.initLoop();
}
