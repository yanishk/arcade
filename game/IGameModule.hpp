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

namespace arcade
{
    class IGameModule
    {
        public:
            IGameModule() {};
            virtual ~IGameModule() = 0;

            virtual std::array<std::string, 19> getMap() = 0;
            virtual std::map<std::string, std::string> getPattern() = 0;

        protected:
        private:
    };
}

#endif /* !IGAMEMODULE_HPP_ */
