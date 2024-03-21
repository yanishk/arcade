/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGameModule.hpp"
#include <map>

namespace arcade
{
    class Nibbler : virtual public IGameModule
    {
        public :
            Nibbler();
            ~Nibbler() = default;

            std::array<std::string, 19> getMap();
            std::map<std::string, std::string> getPattern();
            void updateMap(arcade::KeyPressed key) override;
            void updatePlayerPos() override;
            void stockPlayerPos() override;
            std::pair<std::size_t, std::size_t> getPlayerHeadPos() override;

        private:
            bool isFree(char c);
            std::array<std::string, 19> _map;
            std::map<std::string, std::string> _patternPath;
            std::vector <std::pair<std::size_t, std::size_t>> _snakePos;
    };
}

extern "C"
{
    arcade::Nibbler* entryPoint() {
        return new arcade::Nibbler;
    }
}

#endif /* !NIBBLER_HPP_ */
