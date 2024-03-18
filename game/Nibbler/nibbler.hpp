/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "../IGameModule.hpp"

namespace arcade {
    class Nibbler : virtual public IGameModule {
        public :
            Nibbler();
            ~Nibbler(){};

        private:
            std::array<std::string, 19> _map;
    }
};

#endif /* !NIBBLER_HPP_ */
