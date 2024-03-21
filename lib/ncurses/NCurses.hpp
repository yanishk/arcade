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

            void init(std::map<std::string, std::string>) override;
            void stop() override;
            bool game(std::array<std::string, 19> map) override;
            void textDisplay(const std::string displayText, int xPos, int yPos) override;
            void initSprite(const char *imagePath, int xPos, int yPos) noexcept override {};
            void displayMap(std::array<std::string, 19> map) override;
            arcade::KeyPressed getKey() override;
            void setKey(arcade::KeyPressed newValue) override;
        private:
            arcade::KeyPressed checkKeyPressed(int key);
            WINDOW *_window;
            KeyPressed _key;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::NCurses;
    }
}

#endif /* !NCURSES_HPP_ */
