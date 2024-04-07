/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#include "Nibbler.hpp"
#include <iostream>

arcade::Nibbler::Nibbler() : _score(0), _time(0), _gameName("Nibbler")
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
        "######################################",
        "                                      ",
        "                                      ",
        "                                      ",
        "                                      "
    };
    _map = _defaultMap;
    _patternPath["##"] = std::make_pair(WHITE, "assets/sprites/brick_wall.bmp");
    _patternPath["  "] = std::make_pair(BLACK, "");
    _patternPath["[]"] = std::make_pair(RED, "assets/sprites/apple.png");
    _patternPath["=="] = std::make_pair(BLUE, "");
    _patternPath["8~"] = std::make_pair(GREEN, "");
    _patternPath["<="] = std::make_pair(YELLOW, "");
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
    _sizeCell = 2;
    stockPlayerPos();
}

void arcade::Nibbler::resetGame() noexcept
{
    _map = _defaultMap;
    _snakePos.clear();
    stockPlayerPos();
    _textToDisplay.clear();
    _score = 0;
    _time = 0;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
}

std::string arcade::Nibbler::getGameName() const noexcept
{
    return _gameName;
}

std::size_t arcade::Nibbler::getScore() const noexcept
{
    return _score;
}

std::array<std::string, 23> arcade::Nibbler::getMap() const noexcept
{
    return _map;
}

std::unordered_map<std::string, std::pair<arcade::Color, std::string>> arcade::Nibbler::getPattern() const noexcept
{
    return _patternPath;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::Nibbler::getText() const noexcept
{
    return _textToDisplay;
}

std::size_t arcade::Nibbler::getMapCellSize() const noexcept
{
    return _sizeCell;
}

void arcade::Nibbler::incrementTime() noexcept
{
    _time += 1;
}

std::pair<std::size_t, std::size_t> arcade::Nibbler::getIndexes() const noexcept
{
    return std::make_pair(0, 0);
}

bool arcade::Nibbler::isAvailable(const char c) const noexcept
{
    return (c == ' ' || c == '[' || c == ']');
}

bool arcade::Nibbler::isFood(const char firstChar, const char secondChar) const noexcept
{
    return ((firstChar == '[' && secondChar == ']') ||
        (secondChar == '[' && firstChar == ']'));
}

bool arcade::Nibbler::isSnakeBody(const char firstChar, const char secondChar) const noexcept
{
    return ((firstChar == '=' && secondChar == '=') ||
        (firstChar == '<' && secondChar == '=') ||
        (firstChar == '=' && secondChar == '<'));
}

bool arcade::Nibbler::isNeckPattern1(const std::pair <std::size_t, std::size_t> cell1,
    const std::pair <std::size_t, std::size_t> cell2) const noexcept
{
    return (_snakePos[_snakePos.size() - 3].first == cell1.first &&
        _snakePos[_snakePos.size() - 3].second == cell1.second &&
        _snakePos[_snakePos.size() - 4].first == cell2.first &&
        _snakePos[_snakePos.size() - 4].second == cell2.second);
}

bool arcade::Nibbler::isNeckPattern2(const std::pair <std::size_t, std::size_t> cell1,
    const std::pair <std::size_t, std::size_t> cell2) const noexcept
{
    return (_snakePos[_snakePos.size() - 3].first == cell2.first &&
        _snakePos[_snakePos.size() - 3].second == cell2.second &&
        _snakePos[_snakePos.size() - 4].first == cell1.first &&
        _snakePos[_snakePos.size() - 4].second == cell1.second);
}

bool arcade::Nibbler::isSnakeNeck(const std::pair <std::size_t, std::size_t> cell1,
    const std::pair <std::size_t, std::size_t> cell2) const noexcept
{
    return (isNeckPattern1(cell1, cell2) || isNeckPattern2(cell1, cell2));
}

bool arcade::Nibbler::checkLoose(const std::pair <std::size_t, std::size_t> cell1,
    const std::pair <std::size_t, std::size_t> cell2) const noexcept
{
    return (isSnakeBody(_map[cell1.first][cell1.second],
        _map[cell2.first][cell2.second]) && !isSnakeNeck(cell1, cell2));
}

bool arcade::Nibbler::checkWin() const noexcept
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

bool arcade::Nibbler::isTJunctionUp(const std::size_t x, const std::size_t y) const noexcept
{
    return (_map[x - 1][y] == '#' &&
        _map[x][y - 2] == ' ' &&
        _map[x][y + 1] == ' ');
}
bool arcade::Nibbler::isTJunctionDown(const std::size_t x, const  std::size_t y) const noexcept
{
    return (_map[x + 1][y] == '#' &&
        _map[x][y - 2] == ' ' &&
        _map[x][y + 1] == ' ');
}

bool arcade::Nibbler::isTJunctionRight(const std::size_t x, const std::size_t y) const noexcept
{
    return (_map[x][y - 2] == '#' &&
        _map[x + 1][y] == ' ' &&
        _map[x - 1][y] == ' ');
}

bool arcade::Nibbler::isTJunctionLeft(const std::size_t x, const std::size_t y) const noexcept
{
    return (_map[x][y + 1] == '#' &&
        _map[x + 1][y] == ' ' &&
        _map[x - 1][y] == ' ');
}

bool arcade::Nibbler::isTJunction(const std::size_t x, const std::size_t y) const noexcept
{
    return (isTJunctionUp(x,y) || isTJunctionDown(x,y) ||
        isTJunctionRight(x,y) || isTJunctionLeft(x,y));
}

void arcade::Nibbler::increaseScore() noexcept
{
    _score += 100;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.pop_back();
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
}

void arcade::Nibbler::growSnakeTail(const std::pair <std::size_t, std::size_t> snakeTailCell1,
    const std::pair <std::size_t, std::size_t> snakeTailCell2) noexcept
{
    _map[_snakePos[0].first][_snakePos[0].second] = '=';
    _map[snakeTailCell1.first][snakeTailCell1.second] = '<';
    _map[snakeTailCell2.first][snakeTailCell2.second] =  '=';
    _snakePos.insert(_snakePos.begin(),
        std::make_pair(snakeTailCell2.first, snakeTailCell2.second));
    _snakePos.insert(_snakePos.begin(),
        std::make_pair(snakeTailCell1.first, snakeTailCell1.second));
}

arcade::GameStatus arcade::Nibbler::goUp(const std::size_t x, const std::size_t y) noexcept
{
    bool foodEaten = false;
    std::pair <std::size_t, std::size_t> snakeTailCell1 =
    std::make_pair(_snakePos[0].first, _snakePos[0].second);
    std::pair <std::size_t, std::size_t> snakeTailCell2 =
    std::make_pair(_snakePos[1].first, _snakePos[1].second);

    if (checkLoose(std::make_pair(x - 1, y - 1), std::make_pair(x - 1, y)))
        return LOOSE;
    if (isFood(_map[x - 1][y - 1], _map[x - 1][y])) {
        foodEaten = true;
        increaseScore();
    }
    if (isAvailable(_map[x - 1][y - 1]) && isAvailable(_map[x - 1][y])) {
        updatePlayerPos(std::make_pair(x - 1, y - 1),
            std::make_pair(x - 1, y), std::make_pair(x, y));
        _snakePos[_snakePos.size() - 1].first -= 1;
        _snakePos[_snakePos.size() - 2].first -= 1;
    }
    if (foodEaten)
        growSnakeTail(snakeTailCell1, snakeTailCell2);
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::goDown(const std::size_t x, const std::size_t y) noexcept
{
    bool foodEaten = false;
    std::pair <std::size_t, std::size_t> snakeTailCell1 =
    std::make_pair(_snakePos[0].first, _snakePos[0].second);
    std::pair <std::size_t, std::size_t> snakeTailCell2 =
    std::make_pair(_snakePos[1].first, _snakePos[1].second);

    if (checkLoose(std::make_pair(x + 1, y - 1), std::make_pair(x + 1, y)))
        return LOOSE;
    if (isFood(_map[x + 1][y - 1], _map[x + 1][y])) {
        foodEaten = true;
        increaseScore();
    }
    if (isAvailable(_map[x + 1][y - 1]) && isAvailable(_map[x + 1][y])) {
        updatePlayerPos(std::make_pair(x + 1, y - 1),
            std::make_pair(x + 1, y), std::make_pair(x, y));
        _snakePos[_snakePos.size() - 1].first += 1;
        _snakePos[_snakePos.size() - 2].first += 1;
    }
    if (foodEaten)
        growSnakeTail(snakeTailCell1, snakeTailCell2);
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::goLeft(const std::size_t x, const std::size_t y) noexcept
{
    bool foodEaten = false;
    std::pair <std::size_t, std::size_t> snakeTailCell1 =
    std::make_pair(_snakePos[0].first, _snakePos[0].second);
    std::pair <std::size_t, std::size_t> snakeTailCell2 =
    std::make_pair(_snakePos[1].first, _snakePos[1].second);

    if (checkLoose(std::make_pair(x, y - 3), std::make_pair(x, y - 2)))
        return LOOSE;
    if (isFood(_map[x][y - 2], _map[x][y - 3])) {
        foodEaten = true;
        increaseScore();
    }
    if (isAvailable(_map[x][y - 2]) && isAvailable(_map[x][y - 3])) {
        updatePlayerPos(std::make_pair(x, y - 3),
            std::make_pair(x, y - 2), std::make_pair(x, y));
        _snakePos[_snakePos.size() - 1].second -= 2;
        _snakePos[_snakePos.size() - 2].second -= 2;
    }
    if (foodEaten)
        growSnakeTail(snakeTailCell1, snakeTailCell2);
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::goRight(const std::size_t x, const std::size_t y) noexcept
{
    bool foodEaten = false;
    std::pair <std::size_t, std::size_t> snakeTailCell1 =
    std::make_pair(_snakePos[0].first, _snakePos[0].second);
    std::pair <std::size_t, std::size_t> snakeTailCell2 =
    std::make_pair(_snakePos[1].first, _snakePos[1].second);

    if (checkLoose(std::make_pair(x, y + 1), std::make_pair(x, y + 2)))
        return LOOSE;
    if (isFood(_map[x][y + 1], _map[x][y + 2])) {
        foodEaten = true;
        increaseScore();
    }
    if (isAvailable(_map[x][y + 1]) && isAvailable(_map[x][y + 2])) {
        updatePlayerPos(std::make_pair(x, y + 1),
            std::make_pair(x, y + 2), std::make_pair(x, y));
        _snakePos[_snakePos.size() - 1].second += 2;
        _snakePos[_snakePos.size() - 2].second += 2;
    }
    if (foodEaten)
        growSnakeTail(snakeTailCell1, snakeTailCell2);
    return PLAYING;
}

void arcade::Nibbler::updatePlayerPos(const std::pair<std::size_t, std::size_t> newCell1,
    const std::pair<std::size_t, std::size_t> newCell2,
    const std::pair<std::size_t, std::size_t> playerHead) noexcept
{
    std::size_t i;

    _map[newCell1.first][newCell1.second] =
        _map[playerHead.first][playerHead.second - 1];
    _map[newCell2.first][newCell2.second] =
        _map[playerHead.first][playerHead.second];
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

std::pair<std::size_t, std::size_t> arcade::Nibbler::getPlayerHeadPos() const noexcept
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

void arcade::Nibbler::stockPlayerPos() noexcept
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

arcade::GameStatus arcade::Nibbler::updateMap(arcade::KeyPressed key) noexcept
{
    std::pair<std::size_t, std::size_t> playerPos = getPlayerHeadPos();
    GameStatus status = PLAYING;

    if (checkWin())
        return WON;
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    if (key == UP)
        status = goUp(playerPos.first, playerPos.second);
    if (key == DOWN)
        status = goDown(playerPos.first, playerPos.second);
    if (key == LEFT)
        status = goLeft(playerPos.first, playerPos.second);
    if (key == RIGHT)
        status = goRight(playerPos.first, playerPos.second);
    if (key == R) {
        resetGame();
        status = RESET;
    }
    if (nextPlayerMove() == LOOSE)
        return LOOSE;
    if (key == M)
        return MENU;
    return status;
}

arcade::GameStatus arcade::Nibbler::movingPlayerRight(const std::size_t x,
    const std::size_t y) noexcept
{
    if (checkLoose(std::make_pair(x, y + 1),
        std::make_pair(x, y + 2)))
        return LOOSE;
    if (isAvailable(_map[x][y + 1]) && isAvailable(_map[x][y + 2]))
        return goRight(x, y);
    return NO_ACTIVITY;
}

arcade::GameStatus arcade::Nibbler::movingPlayerUp(const std::size_t x,
    const std::size_t y) noexcept
{
    if (checkLoose(std::make_pair(x - 1, y - 1),
        std::make_pair(x - 1, y)))
        return LOOSE;
    if (isAvailable(_map[x - 1][y - 1]) && isAvailable(_map[x - 1][y]))
        return goUp(x, y);
    return NO_ACTIVITY;
}

arcade::GameStatus arcade::Nibbler::movingPlayerLeft(const std::size_t x,
    const std::size_t y) noexcept
{
    if (checkLoose(std::make_pair(x, y - 2),
        std::make_pair(x, y - 3)))
        return LOOSE;
    if (isAvailable(_map[x][y - 2]) && isAvailable(_map[x][y - 3]))
        return goLeft(x, y);
    return NO_ACTIVITY;
}

arcade::GameStatus arcade::Nibbler::movingPlayerDown(const std::size_t x,
    const std::size_t y) noexcept
{
    if (checkLoose(std::make_pair(x + 1, y - 1),
        std::make_pair(x + 1, y)))
        return LOOSE;
    if (isAvailable(_map[x + 1][y - 1]) && isAvailable(_map[x + 1][y]))
        return goDown(x, y);
    return NO_ACTIVITY;
}

arcade::GameStatus arcade::Nibbler::checkMovingPlayer(const arcade::KeyPressed
    lastMove, const std::size_t x, const std::size_t y) noexcept
{
    if (lastMove == RIGHT)
        return movingPlayerRight(x, y);
    if (lastMove == UP)
        return movingPlayerUp(x, y);
    if (lastMove == LEFT)
        return movingPlayerLeft(x, y);
    if (lastMove == DOWN)
        return movingPlayerDown(x, y);
    return NO_ACTIVITY;
}

arcade::GameStatus arcade::Nibbler::checkRightCell(const std::size_t x,
    const std::size_t y, KeyPressed &lastMove) noexcept
{
    goRight(x, y);
    lastMove = RIGHT;
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::checkUpCell(const std::size_t x,
    const std::size_t y, KeyPressed &lastMove) noexcept
{
    goUp(x, y);
    lastMove = UP;
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::checkLeftCell(const std::size_t x,
    const std::size_t y, KeyPressed &lastMove) noexcept
{
    goLeft(x, y);
    lastMove = LEFT;
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::checkDownCell(const std::size_t x,
    const std::size_t y, KeyPressed &lastMove) noexcept
{
    goDown(x, y);
    lastMove = DOWN;
    return PLAYING;
}

arcade::GameStatus arcade::Nibbler::nextPlayerMove() noexcept
{
    std::pair<std::size_t, std::size_t> playerPos = getPlayerHeadPos();
    std::size_t x = playerPos.first;
    std::size_t y = playerPos.second;
    static KeyPressed lastMove = OTHER;
    GameStatus status = checkMovingPlayer(lastMove, x, y);

    if (isTJunction(x, y))
        return PLAYING;
    if (status != NO_ACTIVITY)
        return status;
    if (isAvailable(_map[x][y + 1]) && isAvailable(_map[x][y + 2]))
        return checkRightCell(x, y, lastMove);
    if (isAvailable(_map[x - 1][y - 1]) && isAvailable(_map[x - 1][y]))
        return checkUpCell(x, y, lastMove);
    if (isAvailable(_map[x][y - 2]) && isAvailable(_map[x][y - 3]))
        return checkLeftCell(x, y, lastMove);
    if (isAvailable(_map[x + 1][y - 1]) && isAvailable(_map[x + 1][y]))
        return checkDownCell(x, y, lastMove);
    return PLAYING;
}
