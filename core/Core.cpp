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
#include <filesystem>

void arcade::Core::readLib(std::string libPath)
{
    std::string path = "lib";

    for (auto it = _libName.begin(); it != _libName.end(); it++) {
        if (*it == libPath) {
            _lib.push_back(openLib(libPath));
            _libText.push_back(libPath);
        }
    }
    if (_lib.size() == 0)
        exit(84);
    for (auto &entry : std::filesystem::directory_iterator(path)) {
        for (auto it = _libName.begin(); it != _libName.end(); it++) {
            if (*it == entry.path().string() && *it != libPath) {
                _lib.push_back(openLib(*it));
                _libText.push_back(*it);
            }
        }
        for (auto it = _gameName.begin(); it != _gameName.end(); it++) {
            if (*it == entry.path().string()) {
                _game.push_back(openGame(*it));
                _gameText.push_back(*it);
            }
        }
    }
}

arcade::Core::Core(std::string libPath)
{
    _libName =
    {
        "lib/arcade_sdl2.so",
        "lib/arcade_sfml.so",
        "lib/arcade_ncurses.so",
    };
    _gameName =
    {
        "lib/arcade_menu.so",
        "lib/arcade_nibbler.so",
        "lib/arcade_pacman.so"
    };
    readLib(libPath);
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

void arcade::Core::manageMenuSwitchLib(std::size_t indexLib, std::size_t indexGame, std::size_t tmp)
{
    if (tmp != indexLib) {
        _lib[tmp]->stop();
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
}

void arcade::Core::manageMenuSwitchGame(std::size_t indexLib, std::size_t indexGame, std::size_t tmp)
{
    if (tmp != indexGame) {
        _lib[indexLib]->stop();
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
}

size_t arcade::Core::manageDynamicSwitchLib(std::size_t indexLib, std::size_t indexGame)
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

size_t arcade::Core::manageDynamicSwitchGame(std::size_t indexLib, std::size_t indexGame)
{
    if (_lib[indexLib]->getKey() == G) {
        _game[indexGame]->resetGame();
        _lib[indexLib]->stop();
            indexGame += 1;
        if (indexGame >= _gameText.size())
            indexGame = 1;
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
    return indexGame;
}

void arcade::Core::loop()
{
    GameStatus status = PLAYING;
    std::size_t indexLib = 0;
    std::size_t indexGame = 0;
    std::size_t tmpLib = 0;
    std::size_t tmpGame = 0;
    auto clockT0 = std::chrono::steady_clock::now();
    unsigned int msTimer = 140;

    _lib[indexLib]->init(_game[indexGame]->getPattern());
    _game[indexGame]->initText(_libText, _gameText);
    while (status == PLAYING) {
        auto clockT1 = std::chrono::steady_clock::now();
        auto timeElapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(clockT1 - clockT0);
        if (timeElapsed.count() > msTimer) {
            if (indexGame == 0) {
                indexGame = _game[0]->getIndexes().second;
                manageMenuSwitchGame(indexLib, indexGame, tmpGame);
                tmpGame = indexGame;
                indexLib = _game[0]->getIndexes().first;
                manageMenuSwitchLib(indexLib, indexGame, tmpLib);
                tmpLib = indexLib;
            }
            _lib[indexLib]->displayText(_game[indexGame]->getText());
            _lib[indexLib]->displayMap(_game[indexGame]->getMap(),
            _game[indexGame]->getMapCellSize());
            _lib[indexLib]->game();
            status = _game[indexGame]->updateMap(_lib[indexLib]->getKey());
            clockT0 = std::chrono::steady_clock::now();
            if (indexGame != 0) {
                indexGame = manageDynamicSwitchGame(indexLib, indexGame);
                indexLib = manageDynamicSwitchLib(indexLib, indexGame);
            }
            _lib[indexLib]->setKey(OTHER);
        }
    }
    _lib[indexLib]->stop();
}
