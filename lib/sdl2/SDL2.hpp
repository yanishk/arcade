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
#include <array>
#include <map>

namespace arcade
{
    class SDL2 : virtual public IDisplayModule
    {
        public:
            SDL2() : _name("SDL2") {};
            ~SDL2() {};

            void init(std::map<std::string, std::string> pattern) override;
            void stop() override;
            bool game(std::array<std::string, 19> map) override;
            void textDisplay(const std::string displayText, int xPos, int yPos) override;
            void initSprite(const char *imagePath, int xPos, int yPos) noexcept override;
            void displayMap(std::array<std::string, 19> map) override;
            void initCharMap(std::array<std::string, 19> map);
            void initRectShape(std::string pattern, short r, short g, short b, int xPos, int yPos);
            void pickColor(std::map<std::string, std::string> patternMap);
        private:
            void initWindow();
            void initFont(const char *fontPath);
            std::string _name;
            TTF_Font *_font;
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            SDL_Texture *_message;
            std::map<std::string, std::pair<SDL_Texture *, SDL_Rect>> _charMap;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::SDL2;
    }
}

#endif /* !NCURSES_HPP_ */
