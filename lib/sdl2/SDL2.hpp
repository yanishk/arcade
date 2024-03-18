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
            void textNameDisplay(std::string textDisplay) override;
            bool game() override;
            SDL_Window *_window;
            SDL_Renderer *_screen;
            SDL_Surface *_surfaceMsg;
            SDL_Texture *_Message;
        protected:
        private:
            std::string _name;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::SDL2;
    }
}
#endif /* !NCURSES_HPP_ */
