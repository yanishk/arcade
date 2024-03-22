/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** main
*/


#include "Core.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "invalid number of arguments" << std::endl;
        return 84;
    }
    arcade::Core core(av[1]);
    core.initLoop();
}
