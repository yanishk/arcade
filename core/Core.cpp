/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <iostream>
#include "Core.hpp"
#include <filesystem>

void arcade::Core::readLib(std::string libPath)
{
    std::string path = "lib";

    for (auto it = _libName.begin(); it != _libName.end(); it++) {
        if (*it == libPath) {
            _libLoader.push_back(new DLLoader<IDisplayModule>(libPath));
            _libText.push_back(libPath);
        }
    }
    if (_libLoader.size() == 0)
        exit(84);
    for (auto &entry : std::filesystem::directory_iterator(path)) {
        for (auto it = _libName.begin(); it != _libName.end(); it++) {
            if (*it == entry.path().string() && *it != libPath) {
                _libLoader.push_back(new DLLoader<IDisplayModule>(*it));
                _libText.push_back(*it);
            }
        }
        for (auto it = _gameName.begin(); it != _gameName.end(); it++) {
            if (*it == entry.path().string() && *it == "lib/arcade_menu.so") {
                _gameLoader.insert(_gameLoader.begin(), new DLLoader<IGameModule>(*it));
                _gameText.insert(_gameText.begin(), *it);
            } else if (*it == entry.path().string()) {
                _gameLoader.push_back(new DLLoader<IGameModule>(*it));
                _gameText.push_back(*it);
            }
        }
    }
    for (auto &it : _libLoader) {
        _lib.push_back(it->getInstance());
    }
    for (auto it : _gameLoader)
        _game.push_back(it->getInstance());
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

void arcade::Core::accelerateMovement(arcade::GameStatus &status, unsigned int &msTimer)
{
    if (status == WON_AND_RELOADED) {
        if (msTimer >= 15)
            msTimer -= 15;
        status = PLAYING;
    }
}

void arcade::Core::incrementGameTime(std::chrono::steady_clock::time_point &clockT2,
    std::chrono::steady_clock::time_point &clockT0, std::size_t indexGame)
{
    auto timeElapsed2 = std::chrono::duration_cast
    <std::chrono::seconds>(clockT2 - clockT0);
    if (timeElapsed2.count() >= 1) {
        _game[indexGame]->incrementTime();
        clockT0 = std::chrono::steady_clock::now();
    }
}

void arcade::Core::loop()
{
    GameStatus status = PLAYING;
    std::size_t indexLib = 0;
    std::size_t indexGame = 0;
    std::size_t tmpLib = 0;
    std::size_t tmpGame = 0;
    auto clockT0 = std::chrono::steady_clock::now();
    auto clockT1 = std::chrono::steady_clock::now();
    unsigned int msTimer = 115;

    _lib[indexLib]->init(_game[indexGame]->getPattern());
    _game[indexGame]->initText(_libText, _gameText);
    while (status == PLAYING) {
        auto clockT2 = std::chrono::steady_clock::now();
        auto timeElapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(clockT2 - clockT1);
        if (timeElapsed.count() > msTimer) {
            _lib[indexLib]->changeColor(_game[indexGame]->getPattern());
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
            clockT1 = std::chrono::steady_clock::now();
            indexLib = manageDynamicSwitchLib(indexLib, indexGame);
            indexGame = manageDynamicSwitchGame(indexLib, indexGame);
            _lib[indexLib]->setKey(OTHER);
            incrementGameTime(clockT2, clockT0, indexGame);
        }
        accelerateMovement(status, msTimer);
    }
    _lib[indexLib]->stop();
    for (auto it : _libLoader)
        it->closeLib();
    for (auto it : _gameLoader)
        it->closeLib();
}
