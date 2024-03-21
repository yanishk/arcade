/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#include "Nibbler.hpp"
#include <iostream>

arcade::Nibbler::Nibbler()
{
    _map = {
        "######################################",
        "##    []      []      []      []    ##",
        "##  ######  ##  ######  ##  ######  ##",
        "##[]##  ##[]##          ##[]##  ##[]##",
        "##  ######  ##  ##  ##  ##  ######  ##",
        "##          ##[]##  ##[]##          ##",
        "##  ##########  ##  ##  ##########  ##",
        "##[]##  []                  []  ##[]##",
        "##  ##  ########      ########  ##  ##",
        "##      []                  []      ##",
        "##  ##########  ######  ##########  ##",
        "##    []        ##  ##        []    ##",
        "##  ######  ##  ######  ##  ######  ##",
        "##  ##  ##  ##          ##  ##  ##  ##",
        "##[]######[]##[]######[]##[]######[]##",
        "##          ##  ##  ##  ##          ##",
        "##[]##########  ######  ##########[]##",
        "##          <=========8~            ##",
        "######################################"
    };
    _patternPath["##"] = "White";
    _patternPath["  "] = "Black";
    _patternPath["[]"] = "Red";
    _patternPath["=="] = "Blue";
    _patternPath["8~"] = "Green";
    _patternPath["<="] = "Yellow";
}

bool arcade::Nibbler::isFree(char c)
{
    return (c == ' ' || c == '[' || c == ']');
}

void arcade::Nibbler::updateMap(arcade::KeyPressed key)
{
    std::pair<std::size_t, std::size_t> playerPos = getPlayerHeadPos();

// le faire en plus clean en passant en param l'offset pour le premier char
    if (key == arcade::KeyPressed::UP) {
        if (isFree(_map[playerPos.first - 1][playerPos.second])) {
            _map[playerPos.first - 1][playerPos.second] =
            _map[playerPos.first][playerPos.second];
            updatePlayerPos();
            _snakePos[_snakePos.size() - 1].first -= 1;
        }
    }
    if (key == arcade::KeyPressed::DOWN) {
        if (isFree(_map[playerPos.first + 1][playerPos.second])) {
            _map[playerPos.first + 1][playerPos.second] =
            _map[playerPos.first][playerPos.second];
            updatePlayerPos();
            _snakePos[_snakePos.size() - 1].first += 1;
        }
    }
    if (key == arcade::KeyPressed::LEFT) {
        if (isFree(_map[playerPos.first][playerPos.second - 1])) {
            _map[playerPos.first][playerPos.second - 1] =
            _map[playerPos.first][playerPos.second];
            updatePlayerPos();
            _snakePos[_snakePos.size() - 1].second -= 1;
        }
    }
    if (key == arcade::KeyPressed::RIGHT) {
        if (isFree(_map[playerPos.first][playerPos.second + 1])) {
            _map[playerPos.first][playerPos.second + 1] =
            _map[playerPos.first][playerPos.second];
            updatePlayerPos();
            _snakePos[_snakePos.size() - 1].second += 1;
        }
    }
}

void arcade::Nibbler::updatePlayerPos()
{
    std::size_t i = _snakePos.size() - 1;

    for (i; i > 0; i -= 1) {
        _map[_snakePos[i].first][_snakePos[i].second] =
        _map[_snakePos[i - 1].first][_snakePos[i - 1].second];
    }
    _map[_snakePos[i].first][_snakePos[i].second] = ' ';

    for (i = 0; i != _snakePos.size() - 1; i += 1) {
        _snakePos[i].first = _snakePos[i + 1].first;
        _snakePos[i].second = _snakePos[i + 1].second;
    }
}

void arcade::Nibbler::stockPlayerPos()
{
    for (size_t i = 0; i != 19; i += 1) { // modif avec une variable stockée
        for (size_t y = 0; y != 38; y += 1) { // pareil
            if (_map[i][y] == '<' ||
                _map[i][y] == '='||
                _map[i][y] == '8' ||
                _map[i][y] == '~' ) {
                    _snakePos.push_back(std::make_pair(i, y));
            }
        }
    }

}

std::pair<std::size_t, std::size_t> arcade::Nibbler::getPlayerHeadPos()
{
    size_t i = 0;
    size_t y = 0;

    for (i = 0; i != 19; i += 1) { // modif avec une variable stockée
        for (y = 0; y != 38; y += 1) { // pareil
            if (_map[i][y] == '~') {
                return std::make_pair(i, y);
            }
        }
    }
    return std::make_pair(i, y);
}

std::array<std::string, 19> arcade::Nibbler::getMap()
{
    return _map;
}

std::map<std::string, std::string> arcade::Nibbler::getPattern()
{
    return _patternPath;
}

