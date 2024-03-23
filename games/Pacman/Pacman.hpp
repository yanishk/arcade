/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGameModule.hpp"

namespace arcade
{
    class Pacman : virtual public IGameModule {
        public:
            Pacman() = default;
            ~Pacman() = default;

        protected:
        private:
    };
}

#endif /* !PACMAN_HPP_ */
