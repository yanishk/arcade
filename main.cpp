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
    try {
        arcade::Core core(av[1]);
        core.loop();
    } catch (const arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
