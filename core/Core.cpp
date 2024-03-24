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
        "lib/arcade_ncurses.so",
        "lib/arcade_sdl2.so",
        "lib/arcade_sfml.so",
    };
    _lib.push_back(openLib(libPath));
    for (std::size_t index = 0; index != 3; index += 1) {
        if (libName[index] != libPath)
            _lib.push_back(openLib(libName[index]));
    }
    _game.push_back(openGame("lib/arcade_nibbler.so"));
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

void arcade::Core::managePlayerAutoMoves(std::chrono::steady_clock::time_point &clockT0, int index)
{
    KeyPressed autoMove;
    unsigned int msTimer = 100;
    auto clockT1 = std::chrono::steady_clock::now();
    auto timeElapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(clockT1 - clockT0);

    if (timeElapsed.count() > msTimer) {
        autoMove = _game[0]->nextPlayerMove();
        _lib[index]->setKey(autoMove);
        clockT0 = std::chrono::steady_clock::now();
    }
    if (timeElapsed.count() < msTimer &&
        _lib[index]->getKey() == autoMove)
        _lib[index]->setKey(OTHER);
}

void arcade::Core::loop()
{
    bool exit = false;
    int index = 0;
    auto clockT0 = std::chrono::steady_clock::now();

    _lib[index]->init(_game[0]->getPattern());
    while (!exit) {
        _lib[index]->displayText(_game[0]->getText());
        _lib[index]->game(_game[0]->getMap(), _game[0]->getSize());
        managePlayerAutoMoves(clockT0, index);
        exit = _game[0]->updateMap(_lib[index]->getKey());
        if (_lib[index]->getKey() == N && index < 2) {
            _lib[index]->stop();
            index++;
            _lib[index]->init(_game[0]->getPattern());
        }
        if (_lib[index]->getKey() == P && index > 0) {
            _lib[index]->stop();
            index--;
            _lib[index]->init(_game[0]->getPattern());
        }
        _lib[index]->setKey(OTHER);
    }
    _lib[index]->stop();
}
