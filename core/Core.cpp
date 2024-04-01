/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Core.hpp"

void arcade::Core::createObjectLoader(const std::string libPath) noexcept
{
    std::string path = "lib";

    for (auto &entry : std::filesystem::directory_iterator(path)) {
        for (auto it = _libName.begin(); it != _libName.end(); it++) {
            if (*it == entry.path().string() && *it != libPath) {
                _libLoader.push_back(std::make_unique<DLLoader<IDisplayModule>>(*it));
                _libText.push_back(*it);
            }
        }
        for (auto it = _gameName.begin(); it != _gameName.end(); it++) {
            if (*it == entry.path().string() && *it == "lib/arcade_menu.so") {
                _gameLoader.insert(_gameLoader.begin(), std::make_unique<DLLoader<IGameModule>>(*it));
                _gameText.insert(_gameText.begin(), *it);
            } else if (*it == entry.path().string()) {
                _gameLoader.push_back(std::make_unique<DLLoader<IGameModule>>(*it));
                _gameText.push_back(*it);
            }
        }
    }
}

void arcade::Core::readLib(const std::string libPath)
{

    for (auto it = _libName.begin(); it != _libName.end(); it++) {
        if (*it == libPath) {
            _libLoader.push_back(std::make_unique<DLLoader<IDisplayModule>>(libPath));
            _libText.push_back(libPath);
        }
    }
    if (_libLoader.size() == 0)
        throw arcade::Error("");
    createObjectLoader(libPath);
    for (auto &it : _libLoader) {
        _lib.push_back(it->getInstance());
    }
    for (auto &it : _gameLoader)
        _game.push_back(it->getInstance());
}

arcade::Core::Core(const std::string libPath) : _indexLib(0), _indexGame(0), _tmpLib(0), _tmpGame(0), _score(0)
{
    _libName =
    {
        "lib/arcade_ndk++.so",
        "lib/arcade_aalib.so",
        "lib/arcade_libcaca.so",
        "lib/arcade_allegro5.so",
        "lib/arcade_xlib.so",
        "lib/arcade_gtk+.so",
        "lib/arcade_irrlicht.so",
        "lib/arcade_opengl.so",
        "lib/arcade_vulkan.so",
        "lib/arcade_qt5.so",
        "lib/arcade_sdl2.so",
        "lib/arcade_sfml.so",
        "lib/arcade_ncurses.so"
    };
    _gameName =
    {
        "lib/arcade_menu.so",
        "lib/arcade_snake.so",
        "lib/arcade_nibbler.so",
        "lib/arcade_pacman.so",
        "lib/arcade_qix.so",
        "lib/arcade_centipede.so",
        "lib/arcade_solarfox.so"
    };
    readLib(libPath);
}

void arcade::Core::manageMenuSwitchLib(const std::size_t indexLib, const std::size_t indexGame, const std::size_t tmp) const
{
    if (tmp != indexLib) {
        _lib[tmp]->stop();
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
}

void arcade::Core::manageMenuSwitchGame(const std::size_t indexLib, const std::size_t indexGame, const std::size_t tmp) const
{
    if (tmp != indexGame) {
        _lib[indexLib]->stop();
        _lib[indexLib]->init(_game[indexGame]->getPattern());
    }
}

size_t arcade::Core::manageDynamicSwitchLib(std::size_t indexLib, const std::size_t indexGame) const
{
    if (indexGame != 0) {
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
    }
    return indexLib;
}

size_t arcade::Core::manageDynamicSwitchGame(const std::size_t indexLib, std::size_t indexGame)
{
    if (indexGame != 0) {
        if (_lib[indexLib]->getKey() == G) {
            updateScoreFile(_game[indexGame]->getGameName(), _game[indexGame]->getScore());
            _game[indexGame]->resetGame();
            _lib[indexLib]->stop();
                indexGame += 1;
            if (indexGame >= _gameText.size())
                indexGame = 1;
            _lib[indexLib]->init(_game[indexGame]->getPattern());
        }
    }
    return indexGame;
}

void arcade::Core::updateGame(arcade::GameStatus &status, unsigned int &msTimer,
    const std::size_t indexGame, const std::size_t score) noexcept
{
    if (status == WON_AND_RELOADED) {
        updateScoreFile(_game[indexGame]->getGameName(), score);
        if (msTimer >= 15)
            msTimer -= 15;
        status = PLAYING;
    }
    if (status == RESET) {
        updateScoreFile(_game[indexGame]->getGameName(), score);
        status = PLAYING;
    }
    if (status == LOOSE || status == WON) {
        updateScoreFile(_game[indexGame]->getGameName(), _game[indexGame]->getScore());
        _game[indexGame]->resetGame();
        status = PLAYING;
    }
}

void arcade::Core::incrementGameTime(const std::chrono::steady_clock::time_point clockT2,
    std::chrono::steady_clock::time_point &clockT0, const std::size_t indexGame) const noexcept
{
    auto timeElapsed2 = std::chrono::duration_cast
    <std::chrono::seconds>(clockT2 - clockT0);
    if (timeElapsed2.count() >= 1) {
        _game[indexGame]->incrementTime();
        clockT0 = std::chrono::steady_clock::now();
    }
}

std::vector<std::pair<std::string, std::pair<int, int>>>
    arcade::Core::getGameScores(const std::string gameName) const noexcept
{
    std::vector<std::pair<std::string, std::pair<int, int>>>
        scoreList;
    std::string fileToRead = "." + gameName + ".scores";
    std::string scoreLine;
    int x = 1300;
    int y = 100;

    std::ifstream scoreFile(fileToRead);
    if (!scoreFile.is_open())
        return scoreList;
    scoreList.push_back(std::make_pair(gameName + " scores:", std::make_pair(x, y)));
    x += 15;
    y += 80;
    while (std::getline(scoreFile, scoreLine)) {
        scoreList.push_back(std::make_pair(scoreLine, std::make_pair(x, y)));
        y += 60;
        if (y >= 900) {
            x += 200;
            y = 180;
        }
    }
    scoreFile.close();
    return scoreList;
}

void arcade::Core::updateScoreFile(const std::string gameName, const std::size_t score) noexcept
{
    std::string fileToWrite;

    if (gameName == "Menu")
        return;
    if (_playerName.empty())
        _playerName = "marvin";
    fileToWrite = "." + gameName + ".scores";
    std::ofstream scoreFile(fileToWrite, std::ios::app);
    if (!scoreFile.is_open())
        return;
    scoreFile << _playerName << ": " << score << std::endl;
    scoreFile.close();
}

arcade::GameStatus arcade::Core::handleMenuKey(GameStatus status) noexcept
{
    if (status == MENU) {
        _indexGame = 0;
        _tmpGame = 0;
        _lib[_indexLib]->stop();
        _indexLib = 0;
        _lib[_indexLib]->init(_game[_indexGame]->getPattern());
        _game[_indexGame]->resetGame();
        status = PLAYING;
    }
    return status;
}

void arcade::Core::choseOptionMenu() noexcept
{
    if (_indexGame == 0) {
        _indexGame = _game[0]->getIndexes().second;
        manageMenuSwitchGame(_indexLib, _indexGame, _tmpGame);
        _tmpGame = _indexGame;
        _playerName = _lib[_indexLib]->getPlayerName();
        _indexLib = _game[0]->getIndexes().first;
        manageMenuSwitchLib(_indexLib, _indexGame, _tmpLib);
        _tmpLib = _indexLib;
    }
}

void arcade::Core::endLoop() const noexcept
{
    _lib[_indexLib]->stop();
    for (auto &it : _libLoader) {
        it->closeLib();
        delete (&it);
    }
    for (auto &it : _gameLoader) {
        it->closeLib();
        delete (&it);
    }
}

arcade::GameStatus arcade::Core::mainGame(GameStatus status) noexcept
{
    _score = _game[_indexGame]->getScore();
    _lib[_indexLib]->changeColor(_game[_indexGame]->getPattern());
    choseOptionMenu();
    _lib[_indexLib]->displayText(_game[_indexGame]->getText());
    _lib[_indexLib]->displayText(getGameScores(_game[_indexGame]->getGameName()));
    _lib[_indexLib]->displayMap(_game[_indexGame]->getMap(),
    _game[_indexGame]->getMapCellSize());
    _lib[_indexLib]->game(_game[_indexGame]->getGameName());
    status = _game[_indexGame]->updateMap(_lib[_indexLib]->getKey());
    status = handleMenuKey(status);
    return status;
}

void arcade::Core::loop()
{
    GameStatus status = PLAYING;
    auto clockT0 = std::chrono::steady_clock::now();
    auto clockT1 = std::chrono::steady_clock::now();
    unsigned int msTimer = 115;

    _lib[_indexLib]->init(_game[_indexGame]->getPattern());
    _game[_indexGame]->initText(_libText, _gameText);
    while (status == PLAYING) {
        auto clockT2 = std::chrono::steady_clock::now();
        auto timeElapsed = std::chrono::duration_cast
        <std::chrono::milliseconds>(clockT2 - clockT1);
        if (timeElapsed.count() > msTimer) {
            status = mainGame(status);
            clockT1 = std::chrono::steady_clock::now();
            _indexLib = manageDynamicSwitchLib(_indexLib, _indexGame);
            _indexGame = manageDynamicSwitchGame(_indexLib, _indexGame);
            _lib[_indexLib]->setKey(OTHER);
            incrementGameTime(clockT2, clockT0, _indexGame);
        }
        updateGame(status, msTimer, _indexGame, _score);
    }
    updateScoreFile(_game[_indexGame]->getGameName(), _game[_indexGame]->getScore());
    _lib[_indexLib]->stop();
}
