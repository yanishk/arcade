/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "SDL2.hpp"

void arcade::SDL2::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (TTF_Init())
        exit(84);
    _window = SDL_CreateWindow("SDL2", 20, 20, 1000, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    _screen = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
}

bool arcade::SDL2::game()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    textNameDisplay("Arcade\n");
    SDL_RenderPresent(_screen);
    return false;
}

void arcade::SDL2::stop()
{
    SDL_FreeSurface(_surfaceMsg);
    SDL_DestroyTexture(_Message);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

void arcade::SDL2::textNameDisplay(const std::string displayText)
{
    TTF_Font *sans = TTF_OpenFont("lib/sdl2/asset/font/OpenSans-Regular.ttf", 20);
    if (!sans)
        exit(84);
    SDL_Color White = {255, 255, 255};
    _surfaceMsg = TTF_RenderText_Solid(sans, displayText.c_str(), White);
    if (!_surfaceMsg)
        exit(84);
    _Message = SDL_CreateTextureFromSurface(_screen, _surfaceMsg);
    if (!_Message)
        exit(84);

    SDL_Rect Message_rect;
    Message_rect.x = 200;
    Message_rect.y = 80;
    Message_rect.w = 500;
    Message_rect.h = 100;

    SDL_RenderCopy(_screen, _Message, NULL, &Message_rect);
}

const std::string &arcade::SDL2::getName() const
{
    return _name;
}
