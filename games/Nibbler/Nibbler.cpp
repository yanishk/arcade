/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#include "Nibbler.hpp"
#include <iostream>

arcade::Nibbler::Nibbler() : _score(0)
{
    _defaultMap = {
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
        "##            <=====8~              ##",
        "######################################"
    };
    _map = _defaultMap;
    _patternPath["##"] = WHITE;
    _patternPath["  "] = BLACK;
    _patternPath["[]"] = RED;
    _patternPath["=="] = BLUE;
    _patternPath["8~"] = GREEN;
    _patternPath["<="] = YELLOW;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(_scoreText);
    _sizeMap = 2;
}

void arcade::Nibbler::resetGame()
{
    _map = _defaultMap;
    _snakePos.clear();
    stockPlayerPos();
    _textToDisplay.clear();
    _score = 0;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(_scoreText);
}

bool arcade::Nibbler::isFree(char c)
{
    return (c == ' ' || c == '[' || c == ']');
}

bool arcade::Nibbler::isFood(char c)
{
    return (c == '[' || c == ']');
}

bool arcade::Nibbler::isSnakeBody(char firstChar, char secondChar)
{
    return ((firstChar == '=' && secondChar == '=') ||
        (firstChar == '<' && secondChar == '=') ||
        (firstChar == '=' && secondChar == '<'));
}

bool arcade::Nibbler::isTJunctionUp(std::size_t x,  std::size_t y)
{
    return (_map[x - 1][y] == '#' &&
        _map[x][y - 2] == ' ' &&
        _map[x][y + 1] == ' ');
}
bool arcade::Nibbler::isTJunctionDown(std::size_t x,  std::size_t y)
{
    return (_map[x + 1][y] == '#' &&
        _map[x][y - 2] == ' ' &&
        _map[x][y + 1] == ' ');
}

bool arcade::Nibbler::isTJunctionRight(std::size_t x,  std::size_t y)
{
    return (_map[x][y - 2] == '#' &&
        _map[x + 1][y] == ' ' &&
        _map[x - 1][y] == ' ');
}

bool arcade::Nibbler::isTJunctionLeft(std::size_t x,  std::size_t y)
{
    return (_map[x][y + 1] == '#' &&
        _map[x + 1][y] == ' ' &&
        _map[x - 1][y] == ' ');
}

bool arcade::Nibbler::isTJunction(std::size_t x,  std::size_t y)
{
    return (isTJunctionUp(x,y) || isTJunctionDown(x,y) ||
        isTJunctionRight(x,y) || isTJunctionLeft(x,y));
}

bool arcade::Nibbler::isNotSnakeNeck(std::size_t x, std::size_t y)
{
    return (_snakePos[_snakePos.size() - 3].first != x &&
    _snakePos[_snakePos.size() - 3].second != y &&
    _snakePos[_snakePos.size() - 4].first != x &&
    _snakePos[_snakePos.size() - 4].second != y);
}

void arcade::Nibbler::goUp(std::size_t x, std::size_t y)
{
    if (isSnakeBody(_map[x - 1][y - 1], _map[x - 1][y]) &&
        isNotSnakeNeck((x - 1), (y - 1)) &&
        isNotSnakeNeck((x - 1), (y))) {
        exit(1);
    }
    if (isFood(_map[x - 1][y - 1]) && isFood(_map[x - 1][y])) {
        _score += 100;
        _scoreText = "score: " + std::to_string(_score);
        _textToDisplay.pop_back();
        _textToDisplay.push_back(_scoreText);
    }
    if (isFree(_map[x - 1][y - 1]) && isFree(_map[x - 1][y])) {
        _map[x - 1][y - 1] = _map[x][y - 1];
        _map[x - 1][y] = _map[x][y];
        updatePlayerPos();
        _snakePos[_snakePos.size() - 1].first -= 1;
        _snakePos[_snakePos.size() - 2].first -= 1;
    }
}

void arcade::Nibbler::goDown(std::size_t x, std::size_t y)
{
    if (isSnakeBody(_map[x + 1][y - 1], _map[x + 1][y]) &&
        isNotSnakeNeck((x + 1), (y - 1)) &&
        isNotSnakeNeck((x + 1), (y))) {
        exit(1);
    }
    if (isFood(_map[x + 1][y - 1]) && isFood(_map[x + 1][y])) {
        _score += 100;
        _scoreText = "score: " + std::to_string(_score);
        _textToDisplay.pop_back();
        _textToDisplay.push_back(_scoreText);
    }
    if (isFree(_map[x + 1][y - 1]) && isFree(_map[x + 1][y])) {
        _map[x + 1][y - 1] = _map[x][y - 1];
        _map[x + 1][y] = _map[x][y];
        updatePlayerPos();
        _snakePos[_snakePos.size() - 1].first += 1;
        _snakePos[_snakePos.size() - 2].first += 1;
    }
}

void arcade::Nibbler::goLeft(std::size_t x, std::size_t y)
{
    if (isSnakeBody(_map[x][y - 2], _map[x][y - 3]) &&
        isNotSnakeNeck((x), (y - 2)) &&
        isNotSnakeNeck((x), (y - 3))) {
        exit(1);
    }
    if (isFood(_map[x][y - 2]) && isFood(_map[x][y - 3])) {
        _score += 100;
        _scoreText = "score: " + std::to_string(_score);
        _textToDisplay.pop_back();
        _textToDisplay.push_back(_scoreText);
    }
    if (isFree(_map[x][y - 2]) && isFree(_map[x][y - 3])) {
        _map[x][y - 2] = _map[x][y];
        _map[x][y - 3] = _map[x][y - 1];
        updatePlayerPos();
        _snakePos[_snakePos.size() - 1].second -= 2;
        _snakePos[_snakePos.size() - 2].second -= 2;
    }
}

void arcade::Nibbler::goRight(std::size_t x, std::size_t y)
{
    if (isSnakeBody(_map[x][y + 1], _map[x][y + 2]) &&
        isNotSnakeNeck((x), (y + 1)) &&
        isNotSnakeNeck((x), (y + 2))) {
        exit(1);
    }
    if (isFood(_map[x][y + 1]) && isFood(_map[x][y + 2])) {
        _score += 100;
        _scoreText = "score: " + std::to_string(_score);
        _textToDisplay.pop_back();
        _textToDisplay.push_back(_scoreText);
    }
    if (isFree(_map[x][y + 1]) && isFree(_map[x][y + 2])) {
        _map[x][y + 2] = _map[x][y];
        _map[x][y + 1] = _map[x][y - 1];
        updatePlayerPos();
        _snakePos[_snakePos.size() - 1].second += 2;
        _snakePos[_snakePos.size() - 2].second += 2;
    }
}

arcade::KeyPressed arcade::Nibbler::playerMoveStatus(arcade::KeyPressed lastMove,
    std::size_t x, std::size_t y)
{
    if (lastMove == RIGHT) {
        if (isFree(_map[x][y + 1]) && isFree(_map[x][y + 2]))
            return RIGHT;
    }
    if (lastMove == UP) {
        if (isFree(_map[x - 1][y - 1]) && isFree(_map[x - 1][y]))
            return UP;
    }
    if (lastMove == LEFT) {
        if (isFree(_map[x][y - 2]) && isFree(_map[x][y - 3]))
            return LEFT;
    }
    if (lastMove == DOWN) {
        if (isFree(_map[x + 1][y - 1]) && isFree(_map[x + 1][y]))
            return DOWN;
    }
    return OTHER;
}

arcade::KeyPressed arcade::Nibbler::nextPlayerMove()
{
    std::pair<std::size_t, std::size_t> playerPos = getPlayerHeadPos();
    std::size_t x = playerPos.first;
    std::size_t y = playerPos.second;
    static KeyPressed lastMove;
    KeyPressed playerStatus;

    if (isTJunction(x, y))
        return OTHER;
    playerStatus = playerMoveStatus(lastMove, x, y);
    if (playerStatus != OTHER)
        return playerStatus;
    if (isFree(_map[x][y + 1]) && isFree(_map[x][y + 2]))
        lastMove = RIGHT;
    if (isFree(_map[x - 1][y - 1]) && isFree(_map[x - 1][y]))
        lastMove = UP;
    if (isFree(_map[x][y - 2]) && isFree(_map[x][y - 3]))
        lastMove = LEFT;
    if (isFree(_map[x + 1][y - 1]) && isFree(_map[x + 1][y]))
        lastMove = DOWN;
    return lastMove;
}

bool arcade::Nibbler::updateMap(arcade::KeyPressed key)
{
    std::pair<std::size_t, std::size_t> playerPos = getPlayerHeadPos();

    if (checkWin())
        exit(2);
    if (key == UP)
        goUp(playerPos.first, playerPos.second);
    if (key == DOWN)
        goDown(playerPos.first, playerPos.second);
    if (key == LEFT)
        goLeft(playerPos.first, playerPos.second);
    if (key == RIGHT)
        goRight(playerPos.first, playerPos.second);
    if (key == R_KEY)
        resetGame();
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return true;
    return false;
}

void arcade::Nibbler::updatePlayerPos()
{
    std::size_t i;

    for (i = _snakePos.size() - 1; i > 1; i -= 1) {
        _map[_snakePos[i].first][_snakePos[i].second] =
        _map[_snakePos[i - 2].first][_snakePos[i - 2].second];
    }
    _map[_snakePos[i].first][_snakePos[i].second] = ' ';
    _map[_snakePos[i].first][_snakePos[i].second - 1] = ' ';
    for (i = 0; i != _snakePos.size() - 2; i += 1) {
        _snakePos[i].first = _snakePos[i + 2].first;
        _snakePos[i].second = _snakePos[i + 2].second;
    }
}

void arcade::Nibbler::stockPlayerPos()
{
    for (std::size_t i = 0; i != _map.size(); i += 1) {
        for (std::size_t y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == '<' ||
                _map[i][y] == '='||
                _map[i][y] == '8' ||
                _map[i][y] == '~' ) {
                    _snakePos.push_back(std::make_pair(i, y));
            }
        }
    }
}

bool arcade::Nibbler::checkWin()
{
    for (std::size_t i = 0; i != _map.size(); i += 1) {
        for (std::size_t y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == '[' || _map[i][y] == ']') {
                return false;
            }
        }
    }
    return true;
}

std::pair<std::size_t, std::size_t> arcade::Nibbler::getPlayerHeadPos()
{
    std::size_t i = 0;
    std::size_t y = 0;

    for (i = 0; i != _map.size(); i += 1) {
        for (y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == '~') {
                return std::make_pair(i, y);
            }
        }
    }
    return std::make_pair(i, y);
}

std::vector<std::string> arcade::Nibbler::getText()
{
    return _textToDisplay;
}

std::array<std::string, 19> arcade::Nibbler::getMap()
{
    return _map;
}

std::map<std::string, arcade::Color> arcade::Nibbler::getPattern()
{
    return _patternPath;
}

std::size_t arcade::Nibbler::getSize()
{
    return _sizeMap;
}
