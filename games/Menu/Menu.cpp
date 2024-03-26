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
    _textToDisplay.push_back(std::make_pair("Arcade", std::make_pair(925, 0)));
    _textToDisplay.push_back(std::make_pair("lib/lib_ncurses.so", std::make_pair(300, 200)));
    _textToDisplay.push_back(std::make_pair("lib/lib_sfml.so", std::make_pair(300, 500)));
    _textToDisplay.push_back(std::make_pair("lib/lib_sdl2.so", std::make_pair(300, 800)));
    _textToDisplay.push_back(std::make_pair("lib/lib_nibbler.so", std::make_pair(1400, 200)));
    _textToDisplay.push_back(std::make_pair("lib/lib_pacman.so", std::make_pair(1400, 500)));
    _textToDisplay.push_back(std::make_pair("->", std::make_pair(200, 200)));
    _sizeCell = 1;
    _libSelected = false;
}

std::array<std::string, 21> arcade::Menu::getMap()
{
    return _map;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::Menu::getText()
{
    return _textToDisplay;
}

std::size_t arcade::Menu::getMapCellSize()
{
    return _sizeCell;
}

std::map<std::string, arcade::Color> arcade::Menu::getPattern()
{
    return _patternPath;
}

void arcade::Menu::keyDown()
{
    for (auto &it : _textToDisplay) {
        if (it.first == "->") {
            if ((_libSelected == false && it.second.second < 800)
            || (_libSelected == true && it.second.second < 500))
                it.second.second += 300;
        }
    }
}

void arcade::Menu::keyUp()
{
    for (auto &it : _textToDisplay) {
        if (it.first == "->" && it.second.second > 200)
            it.second.second -= 300;
    }
}

void arcade::Menu::keyEnter()
{
    int xPos = 0;
    int yPos = 0;

    for (auto &it : _textToDisplay) {
        if (it.first == "->" && _libSelected == false) {
            xPos = it.second.first;
            yPos = it.second.second;
            it.second.first = 1300;
            it.second.second = 200;
            _textToDisplay.push_back(std::make_pair("X", std::make_pair(xPos, yPos)));
        }
    }
}

arcade::GameStatus arcade::Menu::updateMap(arcade::KeyPressed key)
{
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    if (key == DOWN)
        keyDown();
    if (key == UP)
        keyUp();
    if (key == ENTER) {
        keyEnter();
        _libSelected = true;
    }
    return PLAYING;
}

bool arcade::Menu::isAvailable(char c)
{
    return (c == ' ');
}
