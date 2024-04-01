/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "SDL2.hpp"
#include "Error.hpp"

arcade::SDL2::SDL2() : _key(OTHER)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initFont("display/asset/font/OpenSans-Regular.ttf");
}

arcade::SDL2::~SDL2()
{
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void arcade::SDL2::initWindow()
{
    _window = SDL_CreateWindow("SDL2", 20, 20, 1920, 1080,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!_window)
        throw arcade::Error(SDL_GetError());
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
        throw arcade::Error(SDL_GetError());
}

void arcade::SDL2::initSurface()
{
    _spriteSurface = SDL_CreateRGBSurface(0, 780, 480, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (!_spriteSurface)
        throw arcade::Error(SDL_GetError());
}

void arcade::SDL2::initFont(const char *fontPath)
{
    if (TTF_Init() == -1)
        throw arcade::Error(SDL_GetError());
    _font = TTF_OpenFont(fontPath, 20);
    if (!_font)
        throw arcade::Error(SDL_GetError());
}

void arcade::SDL2::init(const std::unordered_map<std::string, Color> pattern)
{
    initWindow();
    initSurface();
    pickColor(pattern);
}

arcade::KeyPressed arcade::SDL2::checkKeyPressed(const SDL_Event event) const noexcept
{
    if (event.key.keysym.sym == SDLK_BACKSPACE)
        return BACKSPACE;
    if (event.key.keysym.sym == SDLK_UP)
        return UP;
    if (event.key.keysym.sym == SDLK_DOWN)
        return DOWN;
    if (event.key.keysym.sym == SDLK_LEFT)
        return LEFT;
    if (event.key.keysym.sym == SDLK_RIGHT)
        return RIGHT;
    if (event.key.keysym.sym == SDLK_r)
        return R;
    if (event.key.keysym.sym == SDLK_p)
        return P;
    if (event.key.keysym.sym == SDLK_n)
        return N;
    if (event.key.keysym.sym == SDLK_g)
        return G;
    if (event.key.keysym.sym == SDLK_m)
        return M;
    if (event.key.keysym.sym == SDLK_RETURN)
        return ENTER;
    return OTHER;
}

void arcade::SDL2::setKey(const arcade::KeyPressed newValue) noexcept
{
    _key = newValue;
}

arcade::KeyPressed arcade::SDL2::getKey() const noexcept
{
    return _key;
}

void arcade::SDL2::displayPlayerName(const std::string gameName)
{
    if (gameName != "Menu")
        return;
    std::string playerName = "Player name: " + _playerName;
    SDL_Color White = {255, 255, 255, 255};
    SDL_Surface *surfaceMsg = TTF_RenderText_Solid(_font, playerName.c_str(), White);
    SDL_Rect Message_rect;
    if (!surfaceMsg)
        throw arcade::Error(SDL_GetError());
    _message = SDL_CreateTextureFromSurface(_renderer, surfaceMsg);
    if (!_message)
        throw arcade::Error(SDL_GetError());
    Message_rect = {0, 0, surfaceMsg->w, surfaceMsg->h};
    SDL_FreeSurface(surfaceMsg);
    SDL_RenderCopy(_renderer, _message, NULL, &Message_rect);
}

void arcade::SDL2::game(const std::string gameName) noexcept
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            _key = CLOSE_BUTTON;
        if (event.type == SDL_KEYDOWN)
            _key = checkKeyPressed(event);
        if (gameName == "Menu" && event.type == SDL_TEXTINPUT)
            _playerName += event.text.text;
    }
    displayPlayerName(gameName);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
}

void arcade::SDL2::stop() noexcept
{
    SDL_FreeSurface(_spriteSurface);
    SDL_DestroyTexture(_message);
    SDL_DestroyWindow(_window);
}

void arcade::SDL2::displayMap(const std::array<std::string, 23> map, const std::size_t size) noexcept
{
    size_t y = 0;
    std::string hay;
    int xPos = 0;
    int yPos = 40;

    for (size_t x = 0; x != map.size(); x += 1) {
        while (y != map[0].size()) {
            if (size == 2)
                hay = std::string(1, map[x][y]) + std::string(1, map[x][y+1]);
            else
                hay = std::string(1, map[x][y]);
            auto it = _charMap.find(hay);
            if (it != _charMap.end()) {
                SDL_Rect spriteRect = {xPos, yPos, 40, 40};
                SDL_RenderCopy(_renderer, it->second, NULL, &spriteRect);
            }
            xPos += 40;
            y += size;
        }
        xPos = 0;
        yPos += 40;
        y = 0;
    }
}

void arcade::SDL2::displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    for (auto it : textToDisplay) {
        SDL_Color White = {255, 255, 255, 255};
        SDL_Surface *surfaceMsg = TTF_RenderText_Solid(_font, it.first.c_str(), White);
        if (!surfaceMsg)
            throw arcade::Error(SDL_GetError());
        _message = SDL_CreateTextureFromSurface(_renderer, surfaceMsg);
        if (!_message)
            throw arcade::Error(SDL_GetError());
        SDL_Rect Message_rect = {it.second.first, it.second.second, surfaceMsg->w, surfaceMsg->h};
        SDL_FreeSurface(surfaceMsg);
        SDL_RenderCopy(_renderer, _message, NULL, &Message_rect);
    }
}

void arcade::SDL2::changeColor(const std::unordered_map<std::string, Color> patternMap)
{
    pickColor(patternMap);
}

void arcade::SDL2::pickColor(const std::unordered_map<std::string, Color> patternMap)
{
    for (auto it = patternMap.begin(); it != patternMap.end(); it++) {
        if (it->second == BLACK)
            initRectShape(it->first, 0, 0, 0);
        if (it->second == WHITE)
            initRectShape(it->first, 255, 255, 255);
        if (it->second == RED)
            initRectShape(it->first, 255, 0, 0);
        if (it->second == BLUE)
            initRectShape(it->first, 0, 0, 255);
        if (it->second == GREEN)
            initRectShape(it->first, 0, 128, 0);
        if (it->second == YELLOW)
            initRectShape(it->first, 255, 255, 0);
        if (it->second == YELLOW)
            initRectShape(it->first, 255, 255, 0);
        if (it->second == CYAN)
            initRectShape(it->first, 0, 255, 255);
        if (it->second == GRAY)
            initRectShape(it->first, 150, 150, 150);
    }
}

void arcade::SDL2::initRectShape(const std::string pattern, const short r,
    const short g, const short b)
{
    SDL_Texture* spriteTexture = NULL;

    if (_charMap[pattern] != NULL)
        free(_charMap[pattern]);
    SDL_FillRect(_spriteSurface, NULL, SDL_MapRGB(_spriteSurface->format, r, g, b));
    spriteTexture = SDL_CreateTextureFromSurface(_renderer, _spriteSurface);
    if (!spriteTexture)
        throw arcade::Error(SDL_GetError());
    _charMap[pattern] = spriteTexture;
}

std::string arcade::SDL2::getPlayerName() const noexcept
{
    return _playerName;
}
