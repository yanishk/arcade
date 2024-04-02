/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"
#include <iostream>

void arcade::NCurses::init(const std::unordered_map<std::string, Color> pattern) noexcept
{
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(RED, COLOR_RED, COLOR_RED);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(CYAN, COLOR_CYAN, COLOR_CYAN);
    init_color(8, 150, 150, 150);
    init_pair(GRAY, 8, 8);
    _window = newwin(500, 500, 0, 0);
    pickColor(pattern);
}

void arcade::NCurses::stop() noexcept
{
    delwin(_window);
    endwin();
}

void arcade::NCurses::savePlayerName(const std::string gameName) noexcept
{
    static std::size_t turn = 0;
    char tmp[80] = {0};

    if (gameName == "Menu") {
        if (turn == 0) {
            mvwprintw(_window, 0, 0, "Player name: ");
            wgetstr(_window, tmp);
            _playerName.assign(tmp);
        }
        mvwprintw(_window, 0, 0, "Player name: %s\n", _playerName.c_str());
        wrefresh(_window);
    }
    if (turn == 0) {
        noecho();
        curs_set(false);
        turn += 1;
    }
}

void arcade::NCurses::handleEvent(const std::string gameName) noexcept
{
    savePlayerName(gameName);
    _key = checkKeyPressed(getch());
}

void arcade::NCurses::displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) noexcept
{
    for (auto it : textToDisplay) {
        wattron(_window, COLOR_PAIR(DEFAULT));
        mvwprintw(_window, (it.second.second * 0.03), (it.second.first * 0.1), "%s\n", it.first.c_str());
    }
}

void arcade::NCurses::changeColor(const std::unordered_map<std::string, Color> patternMap) noexcept
{
    pickColor(patternMap);
}

void arcade::NCurses::pickColor(const std::unordered_map<std::string, Color> patternMap) noexcept
{
    _charMap = patternMap;
}

void arcade::NCurses::displayMap(const std::array<std::string, 23> map, const std::size_t size) noexcept
{
    std::size_t index = 1;
    std::string pattern;
    unsigned int colorChosen;

    for (std::size_t x = 0; x != map.size(); x += 1) {
        for (std::size_t y = 0; y != map[0].size(); y += size) {
            if (size == 2)
                pattern = std::string(1, map[x][y]) + std::string(1, map[x][y+1]);
            else
                pattern = std::string(1, map[x][y]);
            auto it = _charMap.find(pattern);
            colorChosen = static_cast<int>(it->second);
            if (it != _charMap.end()) {
                wattron(_window, COLOR_PAIR(colorChosen));
                mvwprintw(_window, x + index, y, "  ");
            }
        }
        wattroff(_window, COLOR_PAIR(colorChosen));
    }
    wrefresh(_window);
}

arcade::KeyPressed arcade::NCurses::checkKeyPressed(const unsigned int key) const noexcept
{
    wclear(_window);
    if (key == KEY_UP)
        return UP;
    if (key == KEY_DOWN)
        return DOWN;
    if (key == KEY_LEFT)
        return LEFT;
    if (key == KEY_RIGHT)
        return RIGHT;
    if (std::toupper(key) == 'R')
        return R;
    if (std::toupper(key) == 'P')
        return P;
    if (std::toupper(key) == 'N')
        return N;
    if (std::toupper(key) == 'G')
        return G;
    if (std::toupper(key) == 'M')
        return M;
    if (key == KEY_BACKSPACE)
        return BACKSPACE;
    if (key == 10)
        return ENTER;
    return OTHER;
}

void arcade::NCurses::setKey(const arcade::KeyPressed newValue) noexcept
{
    _key = newValue;
}

arcade::KeyPressed arcade::NCurses::getKey() const noexcept
{
    return _key;
}

std::string arcade::NCurses::getPlayerName() const noexcept
{
    return _playerName;
}
