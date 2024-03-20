/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "SDL2.hpp"
#include <iostream>
#include <vector>

void arcade::SDL2::initWindow()
{
    _window = SDL_CreateWindow("SDL2", 20, 20, 1000, 1000,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!_window) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
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

void arcade::SDL2::init(std::map<std::string, std::string> pattern)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initWindow();
    initFont("lib/sdl2/asset/font/OpenSans-Regular.ttf");
    pickColor(pattern);
}

bool arcade::SDL2::game(std::array<std::string, 19> map)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    textDisplay("Arcade\n", 80, 100);
    for (auto it = _charMap.begin(); it != _charMap.end(); it++) {
        SDL_RenderCopy(_renderer, it->second.first, NULL, &it->second.second);
    }
    SDL_RenderPresent(_renderer);
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
    _message = SDL_CreateTextureFromSurface(_renderer, surfaceMsg);
    if (!_message) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    SDL_Rect Message_rect = {xPos, yPos, surfaceMsg->w, surfaceMsg->h};
    SDL_FreeSurface(surfaceMsg);
    SDL_RenderCopy(_renderer, _message, NULL, &Message_rect);
}

void arcade::SDL2::initSprite(const char *imagePath, int xPos, int yPos) noexcept
{
    SDL_Surface *spriteSurface = SDL_LoadBMP(imagePath);
    if (!spriteSurface) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(_renderer, spriteSurface);
    if (!spriteTexture) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    SDL_FreeSurface(spriteSurface);

    SDL_Rect spriteRect = {xPos, yPos, spriteSurface->w, spriteSurface->h};
    SDL_RenderCopy(_renderer, spriteTexture, NULL, &spriteRect);
    SDL_RenderPresent(_renderer);
    SDL_DestroyTexture(spriteTexture);
}

void arcade::SDL2::pickColor(std::map<std::string, std::string> patternMap)
{
    int posX = 0;
    int posY = 0;

    for (auto it = patternMap.begin(); it != patternMap.end(); it++) {
        if (it->second == "Black") {
            initRectShape(it->first, 0, 0, 0, posX, posY);
        }
        if (it->second == "White"){
            initRectShape(it->first, 255, 255, 255, posX, posY);
        }
        if (it->second == "Red") {
            initRectShape(it->first, 255, 0, 0, posX, posY);
        }
        if (it->second == "Blue") {
            initRectShape(it->first, 0, 0, 255, posX, posY);
        }
        if (it->second == "Green") {
            initRectShape(it->first, 0, 128, 0, posX, posY);
        }
        if (it->second == "Yellow") {
            initRectShape(it->first, 255, 255, 0, posX, posY);
        }
        posX += 10;
        posY += 10;
    }
}

void arcade::SDL2::initRectShape(std::string pattern, short r, short g, short b, int posX, int posY)
{
    SDL_Surface *spriteSurface = SDL_CreateRGBSurface(0, 780, 480, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (!spriteSurface) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }
    SDL_FillRect(spriteSurface, NULL, SDL_MapRGB(spriteSurface->format, r, g, b));
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(_renderer, spriteSurface);
    if (!spriteTexture) {
        std::cerr << SDL_GetError() << std::endl;
        exit(84);
    }

    SDL_Rect spriteRect = {posX, posY, spriteSurface->w, spriteSurface->h};
    SDL_FreeSurface(spriteSurface);
    _charMap[pattern] = std::make_pair(spriteTexture, spriteRect);
}


void arcade::SDL2::initCharMap(std::array<std::string, 19> map)
{
    std::size_t y = 0;

    for (std::size_t x = 0; x != 19; x += 1) {
        while (y != 38) {
            std::cout << map[x][y];
            y += 2;
        }
        y = 0;
        std::cout << std::endl;
    }
}

void arcade::SDL2::displayMap(std::array<std::string, 19> map)
{
    for (int i = 0; i != 19; i += 1)
        std::cout << map[i] << std::endl;
}
