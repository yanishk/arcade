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
            SDL2();
            ~SDL2();

            void init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern) override;
            void stop() noexcept override;
            void handleEvent(const std::string gameName) noexcept override;
            void changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap) override;
            void displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(const std::array<std::string, 23> map, const std::size_t size) noexcept override;
            KeyPressed getKey() const noexcept override;
            void setKey(const KeyPressed newValue) noexcept override;
            std::string getPlayerName() const noexcept override;

        private:
            void initWindow();
            void initSurface();
            void initFont(const std::string &fontPath);
            void initRectShape(const std::string pattern, const short r,
                const short g, const short b);
            void pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap);
            KeyPressed checkKeyPressed(const SDL_Event event) const noexcept;
            void displayPlayerName(const std::string gameName);
            std::unordered_map<std::string, std::pair<SDL_Texture *, SDL_Texture *>> _charMap;
            void initSprite(const std::string pattern, const std::string pathFile);
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            SDL_Surface *_spriteSurface;
            TTF_Font *_font;
            SDL_Texture *_message;
            KeyPressed _key;
            std::string _playerName;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::SDL2;
    }
}

#endif /* !NCURSES_HPP_ */
