/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

#include "IDisplayModule.hpp"
#include <ncurses.h>
#include <array>

namespace arcade
{
    class NCurses : virtual public IDisplayModule
    {
        public:
            NCurses() = default;
            ~NCurses() = default;

            void init(std::map<std::string, Color> pattern) override;
            void stop() override;
            bool game(std::array<std::string, 19> map) override;
            void displayText(std::vector<std::string> textToDisplay) override;
            void displayMap(std::array<std::string, 19> map) override;
            arcade::KeyPressed getKey() override;
            void setKey(arcade::KeyPressed newValue) override;
            void pickColor(std::map<std::string, Color> patternMap) override;

        private:
            arcade::KeyPressed checkKeyPressed(int key);
            KeyPressed _key;
            std::map<std::string, Color> _charMap;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::NCurses;
    }
}

#endif /* !NCURSES_HPP_ */
