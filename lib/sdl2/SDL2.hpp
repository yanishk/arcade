/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

#include "IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace arcade {
    class SDL2 : virtual public IDisplayModule {
        public:
            SDL2() : _name("SDL2") {};
            ~SDL2() {};

            void init() override;
            void stop() override;
            const std::string &getName() const override;
            void textNameDisplay(const std::string displayText,
                int xPos, int yPos) override;
            bool game() override;
        private:
            void initWindow();
            void initFont(const char *fontPath);
            std::string _name;
            TTF_Font *_font;
            SDL_Window *_window;
            SDL_Renderer *_screen;
            SDL_Texture *_message;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::SDL2;
    }
}
#endif /* !NCURSES_HPP_ */
