/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>

arcade::Menu::Menu()
{
    _textToDisplay.push_back(std::make_pair("->", std::make_pair(200, 200)));
    _textToDisplay.push_back(std::make_pair("X", std::make_pair(5000, 0)));
    _textToDisplay.push_back(std::make_pair("Arcade", std::make_pair(925, 0)));
    _sizeCell = 1;
    _libSelected = false;
    _selectGameArrow = 0;
    _selectLibArrow = 0;
    _indexGame = 0;
    _indexLib = 0;
}

void arcade::Menu::initText(const std::vector<std::string> libName,
    const std::vector<std::string> gameName) noexcept
{
    std::size_t xPos = 300;
    std::size_t yPos = 200;

    for (auto it : libName) {
        _textToDisplay.push_back(std::make_pair(it, std::make_pair(xPos, yPos)));
        yPos += 300;
    }
    xPos = 1400;
    yPos = 200;
    for (auto it : gameName) {
        if (it == "lib/arcade_menu.so")
            continue;
        _textToDisplay.push_back(std::make_pair(it, std::make_pair(xPos, yPos)));
        yPos += 300;
    }
}

std::array<std::string, 23> arcade::Menu::getMap() const noexcept
{
    return _map;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::Menu::getText() const noexcept
{
    return _textToDisplay;
}

std::size_t arcade::Menu::getMapCellSize() const noexcept
{
    return _sizeCell;
}

std::unordered_map<std::string, arcade::Color> arcade::Menu::getPattern() const noexcept
{
    return _patternPath;
}

std::pair<std::size_t, std::size_t> arcade::Menu::getIndexes() const noexcept
{
    return std::make_pair(_indexLib, _indexGame);
}

void arcade::Menu::incrementTime() noexcept
{
    _time += 1;
}

void arcade::Menu::keyDown() noexcept
{
    for (auto &it : _textToDisplay) {
        if (it.first == "->") {
            if ((_libSelected == false && it.second.second < 800)
            || (_libSelected == true && it.second.second < 500)) {
                it.second.second += 300;
                if (_libSelected == false)
                    _selectLibArrow += 1;
                if (_libSelected == true)
                    _selectGameArrow += 1;
            }
        }
        if (it.first == "<-") {
            if (_libSelected == true && it.second.second < 500)
                it.second.second += 300;
        }
    }
}

void arcade::Menu::keyUp() noexcept
{
    for (auto &it : _textToDisplay) {
        if (it.first == "->" && it.second.second > 200) {
            it.second.second -= 300;
            if (_libSelected == false)
                _selectLibArrow -= 1;
            if (_libSelected == true)
                _selectGameArrow -= 1;
        }
        if (it.first == "<-" && it.second.second > 200)
            it.second.second -= 300;
    }
}

void arcade::Menu::keyEnter(const arcade::KeyPressed key) noexcept
{
    int xPos = 0;
    int yPos = 0;

    if (key == ENTER) {
        if (_libSelected == true)
            _gameSelected = true;
        if (_libSelected && _gameSelected) {
            _indexLib = _selectLibArrow;
            _indexGame = _selectGameArrow + 1;
        }
        for (auto &it : _textToDisplay) {
            if (it.first == "->" && _libSelected == false) {
                xPos = it.second.first;
                yPos = it.second.second;
                for (auto &it : _textToDisplay) {
                    if (it.first == "X") {
                        it.second.first = xPos;
                        it.second.second = yPos;
                    }
                }
                it.second.first = 1300;
                it.second.second = 200;
                _libSelected = true;
                _textToDisplay.push_back(std::make_pair("<-", std::make_pair(1700, 200)));
            }
        }
    }
}

arcade::GameStatus arcade::Menu::updateMap(arcade::KeyPressed key) noexcept
{
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    if (key == DOWN)
        keyDown();
    if (key == UP)
        keyUp();
    keyEnter(key);
    return PLAYING;
}
