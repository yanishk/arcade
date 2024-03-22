/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>
#include <map>
#include <array>
#include "KeyPressed.hpp"
#include <vector>

namespace arcade
{
    class IDisplayModule
    {
        public:
            IDisplayModule() = default;
            ~IDisplayModule() = default;

            virtual void init(std::map<std::string, std::string>) = 0;
            virtual void stop() = 0;
            virtual bool game(std::array<std::string, 19> map) = 0;
            virtual void displayText(std::vector<std::string> textToDisplay) = 0;
            virtual void displayMap(std::array<std::string, 19> map) = 0;
            virtual arcade::KeyPressed getKey() = 0;
            virtual void setKey(arcade::KeyPressed newValue) = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */
