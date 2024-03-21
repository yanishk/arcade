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

namespace arcade
{
    class IGameModule
    {
        public:
            IGameModule() = default;
            ~IGameModule() = default;

            virtual std::array<std::string, 19> getMap() = 0;
            virtual std::map<std::string, std::string> getPattern() = 0;
            virtual void updateMap(arcade::KeyPressed key) = 0;
            virtual void updatePlayerPos() = 0;
            virtual void stockPlayerPos() = 0;
            virtual std::pair<std::size_t, std::size_t> getPlayerHeadPos() = 0;

        protected:
        private:
    };
}

#endif /* !IGAMEMODULE_HPP_ */
