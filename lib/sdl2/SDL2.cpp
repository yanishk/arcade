/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "SDL2.hpp"
#include <iostream>

void arcade::SDL2::initWindow()
{
    _window = SDL_CreateWindow("SDL2", 20, 20, 1000, 1000,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!_window) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    _screen = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!_screen) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
}

void arcade::SDL2::initFont(const char *fontPath)
{
    if (TTF_Init() == -1) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    _font = TTF_OpenFont(fontPath, 20);
    if (!_font) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
}

void arcade::SDL2::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initWindow();
    initFont("lib/sdl2/asset/font/OpenSans-Regular.ttf");
}

bool arcade::SDL2::game()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    textDisplay("Arcade\n", 80, 100);
    SDL_RenderPresent(_screen);
    return false;
}

void arcade::SDL2::stop()
{
    SDL_DestroyTexture(_message);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void arcade::SDL2::textDisplay(const std::string displayText, int xPos, int yPos)
{
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMsg = TTF_RenderText_Solid(_font, displayText.c_str(), White);
    if (!surfaceMsg) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    _message = SDL_CreateTextureFromSurface(_screen, surfaceMsg);
    if (!_message) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    SDL_Rect Message_rect = {xPos, yPos, surfaceMsg->w, surfaceMsg->h};
    SDL_FreeSurface(surfaceMsg);
    SDL_RenderCopy(_screen, _message, NULL, &Message_rect);
}

const std::string &arcade::SDL2::getName() const
{
    return _name;
}
