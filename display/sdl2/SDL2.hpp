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
#include <map>

namespace arcade
{
    class SDL2 : virtual public IDisplayModule
    {
        public:
            SDL2() = default;
            ~SDL2() = default;

            void init(std::map<std::string, std::string> pattern) override;
            void stop() override;
            bool game(std::array<std::string, 19> map) override;
            void textDisplay(const std::string displayText, int xPos, int yPos) override;
            void initSprite(const char *imagePath, int xPos, int yPos) noexcept override;
            void displayMap(std::array<std::string, 19> map) override;
            void initRectShape(std::string pattern, short r, short g, short b, int xPos, int yPos);
            void displayRectMap(std::array<std::string, 19> map);
            void pickColor(std::map<std::string, std::string> patternMap);
            arcade::KeyPressed getKey() override;
            void setKey(arcade::KeyPressed newValue) override;
        private:
            void initWindow();
            void initFont(const char *fontPath);
            arcade::KeyPressed checkKeyPressed(SDL_Event event);
            TTF_Font *_font;
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            SDL_Texture *_message;
            std::map<std::string, SDL_Texture *> _charMap;
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
