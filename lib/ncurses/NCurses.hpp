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

namespace arcade
{
    class NCurses : virtual public IDisplayModule
    {
        public:
            NCurses() : _name("Ncurses") {};
            ~NCurses() {};

            void init() override;
            void stop() override;
            void textDisplay(const std::string displayText, int xPos, int yPos) override;
            bool game() override;
            void initSprite(const char *imagePath, int xPos, int yPos) noexcept override {};
        protected:
        private:
            std::string _name;
            WINDOW *_window;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::NCurses;
    }
}
#endif /* !NCURSES_HPP_ */
