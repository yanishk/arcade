/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <string>
#include <array>
#include <map>
#include <vector>
#include "KeyPressed.hpp"
#include "GameStatus.hpp"
#include "Color.hpp"

namespace arcade
{
    class IGameModule
    {
        public:
            IGameModule() = default;
            ~IGameModule() = default;

            virtual void resetGame() = 0;
            virtual std::array<std::string, 21> getMap() = 0;
            virtual std::size_t getMapCellSize() = 0;
            virtual std::map<std::string, Color> getPattern() = 0;
            virtual std::vector<std::string> getText() = 0;
            virtual GameStatus updateMap(arcade::KeyPressed key) = 0;
            virtual KeyPressed nextPlayerMove() = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
