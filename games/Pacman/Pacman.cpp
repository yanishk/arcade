/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Pacman
*/

#include "Pacman.hpp"

arcade::Pacman::Pacman() : _score(0)
{
    _defaultMap = {
        " ################### ",
        " #........#........# ",
        " #!##.###.#.###.##!# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.### # ###.#### ",
        "    #.#       #.#    ",
        "#####.# ##### #.#####",
        "     .  #   #  .     ",
        "#####.# ##### #.#####",
        "    #.#       #.     ",
        " ####.# ##### #.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #!.#.....P.....#.!# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### "
    };
    _map = _defaultMap;
    _patternPath["#"] = BLUE;
    _patternPath[" "] = BLACK;
    _patternPath["."] = WHITE;
    _patternPath["!"] = RED;
    _patternPath["P"] = YELLOW;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
    _sizeCell = 1;
}

void arcade::Pacman::resetGame()
{
    _map = _defaultMap;
    _textToDisplay.clear();
    _score = 0;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
}

std::map<std::string, arcade::Color> arcade::Pacman::getPattern()
{
    return _patternPath;
}

std::size_t arcade::Pacman::getMapCellSize()
{
    return _sizeCell;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::Pacman::getText()
{
    return _textToDisplay;
}


std::array<std::string, 21> arcade::Pacman::getMap()
{
    return _map;
}

std::pair<std::size_t, std::size_t> arcade::Pacman::getPlayerPos()
{
    std::size_t i = 0;
    std::size_t y = 0;

    for (i = 0; i != _map.size(); i += 1) {
        for (y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == 'P') {
                return std::make_pair(i, y);
            }
        }
    }
    return std::make_pair(i, y);
}

bool arcade::Pacman::isAvailable(char c)
{
    return (c == ' ' || c == '.' || c == '!');
}

bool arcade::Pacman::isBigFood(char c)
{
    return (c == '!');
}

bool arcade::Pacman::isLittleFood(char c)
{
    return (c == '.');
}

arcade::Pacman::FOOD arcade::Pacman::whichFood(char c)
{
    if (isBigFood(c))
        return arcade::Pacman::BIGFOOD;
    if (isLittleFood(c))
        return arcade::Pacman::LITTLEFOOD;
    return arcade::Pacman::NOTAFOOD;
}

void arcade::Pacman::increaseScore(arcade::Pacman::FOOD foodType)
{
    if (foodType == LITTLEFOOD)
        _score += 100;
    if (foodType == BIGFOOD)
        _score += 500;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.pop_back();
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
}

arcade::GameStatus arcade::Pacman::goUp(std::size_t x, std::size_t y)
{
    arcade::Pacman::FOOD foodType = whichFood(_map[x - 1][y]);
   if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailable(_map[x - 1][y])) {
        _map[x - 1][y] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goDown(std::size_t x, std::size_t y)
{
    arcade::Pacman::FOOD foodType = whichFood(_map[x + 1][y]);
   if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailable(_map[x + 1][y])) {
        _map[x + 1][y] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goLeft(std::size_t x, std::size_t y)
{
    arcade::Pacman::FOOD foodType = whichFood(_map[x][y - 1]);
   if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailable(_map[x][y - 1])) {
        _map[x][y - 1] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goRight(std::size_t x, std::size_t y)
{
   arcade::Pacman::FOOD foodType = whichFood(_map[x][y + 1]);
   if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailable(_map[x][y + 1])) {
        _map[x][y + 1] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

#include <iostream>

arcade::GameStatus arcade::Pacman::updateMap(arcade::KeyPressed key)
{
    std::pair<std::size_t, std::size_t> playerPos = getPlayerPos();
    std::size_t x = playerPos.first;
    std::size_t y = playerPos.second;
    static KeyPressed lastKey = OTHER;

    if (key != OTHER)
        lastKey = key;
    if (key == OTHER)
        key = lastKey;
    if (checkWin())
        return WON;
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    if (key == UP)
        goUp(x, y);
    if (key == DOWN)
        goDown(x, y);
    if (key == LEFT)
        goLeft(x, y);
    if (key == RIGHT)
        goRight(x, y);
    if (key == R)
        resetGame();
    return PLAYING;
}

bool arcade::Pacman::checkWin()
{
    for (std::size_t i = 0; i != _map.size(); i += 1) {
        for (std::size_t y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == '.' || _map[i][y] == '!') {
                return false;
            }
        }
    }
    return true;
}

std::pair<std::size_t, std::size_t> arcade::Pacman::getIndexes()
{
    return std::make_pair(0, 0);
}
