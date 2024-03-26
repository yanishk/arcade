/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <iostream>
#include "Core.hpp"
#include "DLLoader.hpp"

arcade::Core::Core(std::string libPath)
{
    std::array<std::string, 3> libName =
    {
        "lib/arcade_sdl2.so",
        "lib/arcade_sfml.so",
        "lib/arcade_ncurses.so",
    };
    _lib.push_back(openLib(libPath));
    for (std::size_t index = 0; index != 3; index += 1) {
        if (libName[index] != libPath)
            _lib.push_back(openLib(libName[index]));
    }
    // _game.push_back(openGame("lib/arcade_menu.so"));
    _game.push_back(openGame("lib/arcade_nibbler.so"));
    _game.push_back(openGame("lib/arcade_pacman.so"));
}

arcade::IGameModule *arcade::Core::openGame(std::string path)
{
    arcade::IGameModule *(*cosine)(void);
    char *error;
    void *handle;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    cosine = (arcade::IGameModule *(*)(void)) dlsym(handle, "entryPoint");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(84);
    }
    return (*cosine)();
}

arcade::IDisplayModule *arcade::Core::openLib(std::string path)
{
    arcade::IDisplayModule *(*cosine)(void);
    char *error;
    void *handle;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    cosine = (arcade::IDisplayModule *(*)(void)) dlsym(handle, "entryPoint");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(84);
    }
    return (*cosine)();
}

size_t arcade::Core::manageDynamicSwitchLib(size_t indexLib, size_t indexGame)
{
    if (_lib[indexLib]->getKey() == N && indexLib < 2) {
            _lib[indexLib]->stop();
            indexLib++;
            _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
    if (_lib[indexLib]->getKey() == P && indexLib > 0) {
        _lib[indexLib]->stop();
        indexLib--;
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
    return indexLib;
}

size_t arcade::Core::manageDynamicSwitchGame(size_t indexLib, size_t indexGame)
{
    if (_lib[indexLib]->getKey() == G) {
        _game[indexGame]->resetGame();
        _lib[indexLib]->stop();
        indexGame = !indexGame;
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
    return indexGame;
}

void arcade::Core::loop()
{
    GameStatus status = PLAYING;
    size_t indexLib = 0;
    size_t indexGame = 0;
    auto clockT0 = std::chrono::steady_clock::now();
    unsigned int msTimer = 140;

    _lib[indexLib]->init(_game[indexGame]->getPattern());
    while (status == PLAYING) {
        auto clockT1 = std::chrono::steady_clock::now();
        auto timeElapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(clockT1 - clockT0);
        if (timeElapsed.count() > msTimer) {
            _lib[indexLib]->displayText(_game[indexGame]->getText());
            _lib[indexLib]->displayMap(_game[indexGame]->getMap(),
                _game[indexGame]->getMapCellSize());
            _lib[indexLib]->game();
            status = _game[indexGame]->updateMap(_lib[indexLib]->getKey());
            clockT0 = std::chrono::steady_clock::now();
            indexLib = manageDynamicSwitchLib(indexLib, indexGame);
            indexGame = manageDynamicSwitchGame(indexLib, indexGame);
            _lib[indexLib]->setKey(OTHER);
        }
    }
    _lib[indexLib]->stop();
}
