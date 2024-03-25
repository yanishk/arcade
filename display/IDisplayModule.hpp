/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "KeyPressed.hpp"
#include "Color.hpp"
#include <string>
#include <map>
#include <array>
#include <vector>

namespace arcade
{
    class IDisplayModule
    {
        public:
            IDisplayModule() = default;
            ~IDisplayModule() = default;

            virtual void init(std::map<std::string, Color> pattern) = 0;
            virtual void stop() = 0;
            virtual void game() = 0;
            virtual void displayText(std::vector<std::string> textToDisplay) = 0;
            virtual void displayMap(std::array<std::string, 21> map, std::size_t size) = 0;
            virtual arcade::KeyPressed getKey() = 0;
            virtual void setKey(arcade::KeyPressed newValue) = 0;
            virtual void pickColor(std::map<std::string, Color> patternMap) = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */
