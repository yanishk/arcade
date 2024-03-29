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
#include <iostream>

namespace arcade
{
    class SDL2 : virtual public IDisplayModule
    {
        public:
            SDL2() : _key(OTHER) {};
            ~SDL2() = default;

            void init(std::map<std::string, Color> pattern) override;
            void stop() override;
            void game() override;
            void changeColor(std::map<std::string, Color> patternMap) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            KeyPressed getKey() override;
            void setKey(KeyPressed newValue) override;

        private:
            void initWindow();
            void initSurface();
            void initFont(const char *fontPath);
            void initRectShape(std::string pattern, short r, short g, short b, int xPos, int yPos);
            void pickColor(std::map<std::string, Color> patternMap);
            KeyPressed checkKeyPressed(SDL_Event event);
            std::map<std::string, SDL_Texture *> _charMap;
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            SDL_Surface *_spriteSurface;
            TTF_Font *_font;
            SDL_Texture *_message;
            KeyPressed _key;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::SDL2;
    }
}

#endif /* !NCURSES_HPP_ */
