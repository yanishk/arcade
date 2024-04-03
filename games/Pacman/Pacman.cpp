/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Pacman
*/

#include "Pacman.hpp"
#include <iostream>

arcade::Pacman::Pacman() : _gameName("Pacman"), _score(0),
    _time(0), _turn(0), _canEatGhosts(false)
{
    _defaultMap = {
        "###############################",
        "#..............##.............#",
        "#.####.#######.##.######.####.#",
        "#!####.#######.##.######.####!#",
        "#.............................#",
        "#.####.##.###########.##.####.#",
        "#.####.##......##.....##.####.#",
        "#......#######.##.######......#",
        "######.##.............##.######",
        "###....##.####///####.##....###",
        "###.##.##.###     ###.##.##.###",
        "..........###GG   ###..........",
        "#.####.######   GG######.####.#",
        "..........###     ###..........",
        "#.####.##.###########.##.####.#",
        "#!..##.........P.........##..!#",
        "###.##.##.###########.##.##.###",
        "#......##......##.....##......#",
        "#.############.##.###########.#",
        "#.############.##.###########.#",
        "#.............................#",
        "###############################",
        "                               "
    };
    _map = _defaultMap;
    _patternPath["#"] = std::make_pair(BLUE, "assets/sprites/pacman_wall.bmp");
    _patternPath[" "] = std::make_pair(BLACK, "");
    _patternPath["."] = std::make_pair(WHITE, "");
    _patternPath["!"] = std::make_pair(GREEN, "");
    _patternPath["P"] = std::make_pair(YELLOW, "");
    _patternPath["G"] = std::make_pair(RED, "");
    _patternPath["/"] = std::make_pair(BLUE, "");
    _defaultGhostsPos = getGhostsPos();
    _ghostsPos = _defaultGhostsPos;
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1)
        _ghostsCanChase.push_back(false);
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1)
        _firstExit.push_back(true);
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1)
        _jailTime.push_back(0);
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
    _sizeCell = 1;
}

void arcade::Pacman::resetGame() noexcept
{
    _map = _defaultMap;
    _patternPath["G"] = std::make_pair(RED, "");
    _textToDisplay.clear();
    _defaultGhostsPos.clear();
    _ghostsPos.clear();
    _ghostsCanChase.clear();
    _firstExit.clear();
    _jailTime.clear();
    _canEatGhosts = false;
    _defaultGhostsPos = getGhostsPos();
    _ghostsPos = _defaultGhostsPos;
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1)
        _ghostsCanChase.push_back(false);
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1)
        _firstExit.push_back(true);
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1)
        _jailTime.push_back(0);
    _turn = 0;
    _time = 0;
    _score = 0;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
}

std::string arcade::Pacman::getGameName() const noexcept
{
    return _gameName;
}

std::size_t arcade::Pacman::getScore() const noexcept
{
    return _score;
}

std::unordered_map<std::string, std::pair<arcade::Color, std::string>> arcade::Pacman::getPattern() const noexcept
{
    return _patternPath;
}

std::size_t arcade::Pacman::getMapCellSize() const noexcept
{
    return _sizeCell;
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::Pacman::getText() const noexcept
{
    return _textToDisplay;
}

std::array<std::string, 23> arcade::Pacman::getMap() const noexcept
{
    return _map;
}

std::pair<std::size_t, std::size_t> arcade::Pacman::getIndexes() const noexcept
{
    return std::make_pair(0, 0);
}

void arcade::Pacman::incrementTime() noexcept
{
    _time += 1;
}

std::pair<std::size_t, std::size_t> arcade::Pacman::getPos(char c,
    const std::array<std::string, 23> map) const noexcept
{
    std::size_t i = 0;
    std::size_t y = 0;

    for (i = 0; i != map.size(); i += 1) {
        for (y = 0; y != map[0].size(); y += 1) {
            if (_map[i][y] == c) {
                return std::make_pair(i, y);
            }
        }
    }
    return std::make_pair(i, y);
}

std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>>
    arcade::Pacman::getGhostsPos() const noexcept
{
    std::size_t i = 0;
    std::size_t y = 0;
    std::size_t arrayIndex = 0;
    std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>>
        ghostsPos;

    for (i = 0; i != _map.size(); i += 1) {
        for (y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == 'G') {
                ghostsPos.push_back(std::make_pair(' ', std::make_pair(i, y)));
                arrayIndex += 1;
            }
        }
    }
    return ghostsPos;
}

bool arcade::Pacman::isAvailableForPlayer(const char c) const noexcept
{
    return (c == ' ' || c == '.' || c == '!' || c == 'G');
}

bool arcade::Pacman::isAvailableForGhost(const char c) const noexcept
{
    return (c == ' ' || c == '.' || c == '!' || c == '/' || c == 'P' || c == 'G');
}

bool arcade::Pacman::isBigFood(const char c) const noexcept
{
    return (c == '!');
}

bool arcade::Pacman::isLittleFood(const char c) const noexcept
{
    return (c == '.');
}

bool arcade::Pacman::isGhost(const char c) const noexcept
{
    return (c == 'G');
}

bool arcade::Pacman::isPlayer(const char c) const noexcept
{
    return (c == 'P');
}

arcade::Pacman::Food arcade::Pacman::whichFood(const char c) noexcept
{
    if (isBigFood(c)) {
        _canEatGhosts = true;
        _time = 0;
        return arcade::Pacman::BIGFOOD;
    }
    if (isLittleFood(c))
        return arcade::Pacman::LITTLEFOOD;
    return arcade::Pacman::NOTAFOOD;
}

void arcade::Pacman::increaseScore(const arcade::Pacman::Food foodType) noexcept
{
    if (foodType == LITTLEFOOD)
        _score += 10;
    if (foodType == BIGFOOD)
        _score += 50;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.pop_back();
    _textToDisplay.push_back(std::make_pair(_scoreText, std::make_pair(0, 0)));
}

void arcade::Pacman::resetGhostPosition(const std::size_t i) noexcept
{
    _map[_defaultGhostsPos[i].second.first]
    [_defaultGhostsPos[i].second.second] = 'G';
    _ghostsPos[i].first = _defaultGhostsPos[i].first;
    _ghostsPos[i].second.first = _defaultGhostsPos[i].second.first;
    _ghostsPos[i].second.second = _defaultGhostsPos[i].second.second;
    _ghostsCanChase[i] = false;
    _ghostsPos[i].first = ' ';
    _score += 200;
}

arcade::GameStatus arcade::Pacman::checkGhostUp(const std::size_t x, const std::size_t y) noexcept
{
    _map[x - 1][y] = _map[x][y];
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1) {
        if ((x - 1) == _ghostsPos[i].second.first &&
            y == _ghostsPos[i].second.second)
            resetGhostPosition(i);
    }
    _map[x][y] = ' ';
    return PLAYING;
}


arcade::GameStatus arcade::Pacman::checkGhostDown(const std::size_t x, const std::size_t y) noexcept
{
    _map[x + 1][y] = _map[x][y];
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1) {
        if ((x + 1) == _ghostsPos[i].second.first &&
            y == _ghostsPos[i].second.second)
            resetGhostPosition(i);
    }
    _map[x][y] = ' ';
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::checkGhostLeft(const std::size_t x, const std::size_t y) noexcept
{
    _map[x][y - 1] = _map[x][y];
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1) {
        if (x == _ghostsPos[i].second.first &&
            (y - 1) == _ghostsPos[i].second.second)
            resetGhostPosition(i);
    }
    _map[x][y] = ' ';
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::checkGhostRight(const std::size_t x, const std::size_t y) noexcept
{
    _map[x][y + 1] = _map[x][y];
    for (std::size_t i = 0; i != _ghostsPos.size(); i += 1) {
        if (x == _ghostsPos[i].second.first &&
            (y + 1) == _ghostsPos[i].second.second)
            resetGhostPosition(i);
    }
    _map[x][y] = ' ';
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goUp(const std::size_t x, const std::size_t y) noexcept
{
    arcade::Pacman::Food foodType = whichFood(_map[x - 1][y]);

    if (isGhost(_map[x - 1][y])) {
        if (_canEatGhosts)
            return checkGhostUp(x, y);
        _map[x][y] = ' ';
        return LOOSE;
    }
    if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailableForPlayer(_map[x - 1][y])) {
        _map[x - 1][y] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goDown(const std::size_t x, const std::size_t y) noexcept
{
    arcade::Pacman::Food foodType = whichFood(_map[x + 1][y]);

    if (isGhost(_map[x + 1][y])) {
        if (_canEatGhosts)
            return checkGhostDown(x, y);
        _map[x][y] = ' ';
        return LOOSE;
    }
    if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailableForPlayer(_map[x + 1][y])) {
        _map[x + 1][y] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goLeft(const std::size_t x, const std::size_t y) noexcept
{
    arcade::Pacman::Food foodType = NOTAFOOD;

    if (y == 0) {
        _map[x][y] = ' ';
        _map[x][_map[0].size() - 1] = 'P';
        return PLAYING;
    }
    if (isGhost(_map[x][y - 1])) {
        if (_canEatGhosts)
            return checkGhostLeft(x, y);
        _map[x][y] = ' ';
        return LOOSE;
    }
    foodType = whichFood(_map[x][y - 1]);
    if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailableForPlayer(_map[x][y - 1])) {
        _map[x][y - 1] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::goRight(const std::size_t x, const std::size_t y) noexcept
{
    arcade::Pacman::Food foodType = NOTAFOOD;

    if (y == _map[0].size() - 1) {
        _map[x][y] = ' ';
        _map[x][0] = 'P';
        return PLAYING;
    }
    if (isGhost(_map[x][y + 1])) {
        if (_canEatGhosts)
            return checkGhostRight(x, y);
        _map[x][y] = ' ';
        return LOOSE;
    }
    foodType = whichFood(_map[x][y + 1]);
    if (foodType != NOTAFOOD)
        increaseScore(foodType);
    if (isAvailableForPlayer(_map[x][y + 1])) {
        _map[x][y + 1] = _map[x][y];
        _map[x][y] = ' ';
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::ghostGoUp(std::size_t &x,
    std::size_t &y, char &previousChar, const std::size_t ghostIndex) noexcept
{
    if (isGhost(_map[x - 1][y]))
        return PLAYING;
    if (isPlayer(_map[x - 1][y]) && !_canEatGhosts)
        return LOOSE;
    if (isPlayer(_map[x - 1][y]) && _canEatGhosts)
        return PLAYING;
    char tmp = _map[x - 1][y];
    _map[x - 1][y] = _map[x][y];
    _map[x][y] = previousChar;
    previousChar = tmp;
    _ghostsPos[ghostIndex].second.first -= 1;
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::ghostGoDown(std::size_t &x,
    std::size_t &y, char &previousChar, const std::size_t ghostIndex) noexcept
{
    if (isGhost(_map[x + 1][y]))
        return PLAYING;
    if (isPlayer(_map[x + 1][y]) && !_canEatGhosts)
        return LOOSE;
    if (isPlayer(_map[x + 1][y]) && _canEatGhosts)
        return PLAYING;
    char tmp = _map[x + 1][y];
    _map[x + 1][y] = _map[x][y];
    _map[x][y] = previousChar;
    previousChar = tmp;
    _ghostsPos[ghostIndex].second.first += 1;
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::ghostGoLeft(std::size_t &x,
    std::size_t &y, char &previousChar, const std::size_t ghostIndex) noexcept
{
    if (isGhost(_map[x][y - 1]))
        return PLAYING;
    if (isPlayer(_map[x][y - 1]) && !_canEatGhosts)
        return LOOSE;
    if (isPlayer(_map[x][y - 1]) && _canEatGhosts)
        return PLAYING;
    char tmp = _map[x][y - 1];
    _map[x][y - 1] = _map[x][y];
    _map[x][y] = previousChar;
    previousChar = tmp;
    _ghostsPos[ghostIndex].second.second -= 1;
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::ghostGoRight(std::size_t &x,
    std::size_t &y, char &previousChar, const std::size_t ghostIndex) noexcept
{
    if (isGhost(_map[x][y + 1]))
        return PLAYING;
    if (isPlayer(_map[x][y + 1]) && !_canEatGhosts)
        return LOOSE;
    if (isPlayer(_map[x][y + 1]) && _canEatGhosts)
        return PLAYING;
    char tmp = _map[x][y + 1];
    _map[x][y + 1] = _map[x][y];
    _map[x][y] = previousChar;
    previousChar = tmp;
    _ghostsPos[ghostIndex].second.second += 1;
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::getOutOfBox() noexcept
{
    GameStatus status = PLAYING;

    for (std::size_t i = 0; i != _ghostsCanChase.size(); i += 1) {
        if (_ghostsCanChase[i] && _ghostsPos[i].second.first >= 9 &&
            _ghostsPos[i].second.first <= 13 && _ghostsPos[i].second.second >= 13
            && _ghostsPos[i].second.second <= 17) {
                status = ghostGoUp(_ghostsPos[i].second.first,
                _ghostsPos[i].second.second, _ghostsPos[i].first, i);
                if (status == LOOSE)
                    return status;
        }
    }
    return status;
}

arcade::GameStatus arcade::Pacman::checkGhostDirections(const std::size_t i) noexcept
{
    std::size_t randomNumber = rand() % 4 + 1;

    if (randomNumber == 1 && isAvailableForGhost(_map[_ghostsPos[i].second.first - 1][_ghostsPos[i].second.second]))
        return ghostGoUp(_ghostsPos[i].second.first, _ghostsPos[i].second.second, _ghostsPos[i].first, i);
    if (randomNumber == 2 && isAvailableForGhost(_map[_ghostsPos[i].second.first + 1][_ghostsPos[i].second.second]))
        return ghostGoDown(_ghostsPos[i].second.first, _ghostsPos[i].second.second, _ghostsPos[i].first, i);
    if (_ghostsPos[i].second.second != 0) {
        if (randomNumber == 3 && isAvailableForGhost(_map[_ghostsPos[i].second.first][_ghostsPos[i].second.second - 1]))
            return ghostGoLeft(_ghostsPos[i].second.first, _ghostsPos[i].second.second, _ghostsPos[i].first, i);
    }
    if (_ghostsPos[i].second.second != _map.size() - 1) {
        if (randomNumber == 4 && isAvailableForGhost(_map[_ghostsPos[i].second.first][_ghostsPos[i].second.second + 1]))
            return ghostGoRight(_ghostsPos[i].second.first, _ghostsPos[i].second.second, _ghostsPos[i].first, i);
    }
    return NO_ACTIVITY;
}

arcade::GameStatus arcade::Pacman::moveGhosts() noexcept
{
    std::size_t countCantChase = 0;
    GameStatus status = PLAYING;

    if (getOutOfBox() == LOOSE)
        return LOOSE;
    srand(time(NULL));
    for (std::size_t i = 0;; i += 1) {
        if (i == _ghostsPos.size())
            i = 0;
        if (_ghostsCanChase[i]) {
            status = checkGhostDirections(i);
            if (status != NO_ACTIVITY)
                return status;
        }
        else if (countCantChase == _ghostsPos.size()) {
            break;
        }
        else {
            countCantChase += 1;
        }
    }
    return PLAYING;
}

void arcade::Pacman::setGhostsColor() noexcept
{
    if (_canEatGhosts && _patternPath["G"].first == RED)
        _patternPath["G"] = std::make_pair(CYAN, "");
    if (_canEatGhosts && _time >= 10 &&
        _patternPath["G"].first == CYAN) {
        _patternPath["G"] = std::make_pair(RED, "");
        _canEatGhosts = false;
    }
}

arcade::GameStatus arcade::Pacman::manageGhosts() noexcept
{
    GameStatus status = PLAYING;

    for (std::size_t i = 0; i != _ghostsCanChase.size(); i += 1) {
        if (!_ghostsCanChase[i] && _jailTime[i] == 0 && !_firstExit[i])
            _jailTime[i] = _time + 3;
        if (!_ghostsCanChase[i] && _jailTime[i] == 0 && _firstExit[i]) {
            _jailTime[i] = _time + 10;
            _firstExit[i] = false;
        }
        if (!_ghostsCanChase[i] && _time >= _jailTime[i]
            && _time != 0 && _jailTime[i] != 0) {
            _ghostsCanChase[i] = true;
            _jailTime[i] = 0;
        }
    }
    setGhostsColor();
    status = moveGhosts();
    return status;
}

void arcade::Pacman::impulsePacman(arcade::KeyPressed &key, arcade::KeyPressed &lastKey) noexcept
{
    if (_turn == 0)
        key = LEFT;
    _turn += 1;
    if (key == OTHER)
        key = lastKey;
}

arcade::GameStatus arcade::Pacman::restartGame(arcade::KeyPressed &lastKey) noexcept
{
    if (checkWin() == WON) {
        lastKey = OTHER;
        resetGame();
        return WON_AND_RELOADED;
    }
    return PLAYING;
}

arcade::GameStatus arcade::Pacman::manageKeys(arcade::KeyPressed &key,
    arcade::KeyPressed &lastKey) noexcept
{
    std::pair<std::size_t, std::size_t> playerPos = getPos('P', _map);
    std::size_t x = playerPos.first;
    std::size_t y = playerPos.second;
    GameStatus status = PLAYING;

    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    if (key == UP)
        status = goUp(x, y);
    if (key == DOWN)
        status = goDown(x, y);
    if (key == LEFT)
        status = goLeft(x, y);
    if (key == RIGHT)
        status = goRight(x, y);
    if (key == R) {
        resetGame();
        status = RESET;
    }
    if (key == M)
        return MENU;
    if (key != OTHER)
        lastKey = key;
    return status;
}

arcade::GameStatus arcade::Pacman::updateMap(arcade::KeyPressed key) noexcept
{
    static KeyPressed lastKey = OTHER;
    GameStatus status = PLAYING;

    status = manageGhosts();
    if (status != PLAYING)
        return status;
    impulsePacman(key, lastKey);
    if (restartGame(lastKey) == WON_AND_RELOADED)
        return WON_AND_RELOADED;
    return manageKeys(key, lastKey);
}

bool arcade::Pacman::checkWin() const noexcept
{
    for (std::size_t i = 0; i != _map.size(); i += 1) {
        for (std::size_t y = 0; y != _map[0].size(); y += 1) {
            if (_map[i][y] == '!') {
                return false;
            }
        }
    }
    return true;
}
