/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"

void arcade::NCurses::init(std::map<std::string, Color> pattern)
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    curs_set(false);
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

void arcade::NCurses::stop()
{
    wclear(_window);
    delwin(_window);
    endwin();
}

void arcade::NCurses::game()
{
    _key = checkKeyPressed(getch());
}

void arcade::NCurses::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    for (auto it : textToDisplay) {
        wattron(_window, COLOR_PAIR(DEFAULT));
        mvwprintw(_window, (it.second.second * 0.03), (it.second.first * 0.1), "%s\n", it.first.c_str());
    }
}

void arcade::NCurses::changeColor(std::map<std::string, Color> patternMap)
{
    pickColor(patternMap);
}

void arcade::NCurses::pickColor(std::map<std::string, Color> patternMap)
{
    _charMap = patternMap;
}

void arcade::NCurses::displayMap(std::array<std::string, 23> map, std::size_t size)
{
    int index = 1;
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

arcade::KeyPressed arcade::NCurses::checkKeyPressed(int key)
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
    if (key == KEY_BACKSPACE)
        return BACKSPACE;
    if (key == 10)
        return ENTER;
    return OTHER;
}

void arcade::NCurses::setKey(arcade::KeyPressed newValue)
{
    _key = newValue;
}

arcade::KeyPressed arcade::NCurses::getKey()
{
    return _key;
}
