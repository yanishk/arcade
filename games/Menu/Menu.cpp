/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Menu
*/

#include "Menu.hpp"

arcade::Menu::Menu()
{
    _textToDisplay.push_back(std::make_pair("Arcade", std::make_pair(0, 0)));
    _textToDisplay.push_back(std::make_pair("lib/lib_ncurses.so", std::make_pair(10, 0)));
    _textToDisplay.push_back(std::make_pair("lib/lib_sfml.so", std::make_pair(20, 0)));
    _textToDisplay.push_back(std::make_pair("lib/lib_sdl2.so", std::make_pair(30, 0)));
    _textToDisplay.push_back(std::make_pair("lib/lib_nibbler.so", std::make_pair(40, 0)));
    _textToDisplay.push_back(std::make_pair("lib/lib_pacman.so", std::make_pair(50, 0)));
    _sizeCell = 1;
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

arcade::GameStatus arcade::Menu::updateMap(arcade::KeyPressed key)
{
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    return PLAYING;
}

arcade::KeyPressed arcade::Menu::nextPlayerMove()
{
    return OTHER;
}

std::map<std::string, arcade::Color> arcade::Menu::getPattern()
{
    return _patternPath;
}