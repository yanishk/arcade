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
    start_color();
    curs_set(false);
    pickColor(pattern);
}

void arcade::NCurses::stop()
{
    endwin();
}

bool arcade::NCurses::game(std::array<std::string, 19> map)
{
    int key;

    keypad(stdscr, TRUE);
        displayMap(map);
        key = getch();
        if (key == 27)
            return true;
        _key = checkKeyPressed(key);
    return false;
}

void arcade::NCurses::displayText(std::vector<std::string> textToDisplay)
{
    std::size_t xPos = 0;
    std::size_t yPos = 0;

    for (auto it : textToDisplay) {
        attron(COLOR_PAIR(BLACK));
        mvprintw(xPos, yPos, "%s\n", it.c_str());
        xPos += 50;
    }
}

void arcade::NCurses::pickColor(std::map<std::string, Color> patternMap)
{
    for (auto it = patternMap.begin(); it != patternMap.end(); it++) {
        if (it->second == BLACK) {
            _charMap[it->first] = BLACK;
            init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
        }
        if (it->second == WHITE) {
            _charMap[it->first] = WHITE;
            init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
        }
        if (it->second == RED) {
            _charMap[it->first] = RED;
            init_pair(RED, COLOR_RED, COLOR_RED);
        }
        if (it->second == BLUE) {
            _charMap[it->first] = BLUE;
            init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
        }
        if (it->second == GREEN) {
            _charMap[it->first] = GREEN;
            init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
        }
        if (it->second == YELLOW) {
            _charMap[it->first] = YELLOW;
            init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
        }
    }
}


void arcade::NCurses::displayMap(std::array<std::string, 19> map)
{
    int index = 1;
    std::string pattern;
    unsigned int colorChosen;

    for (std::size_t x = 0; x != map.size(); x += 1) {
        for (std::size_t y = 0; y != map[0].size(); y += 2) {
            pattern = std::string(1, map[x][y]) + std::string(1, map[x][y+1]);
            auto it = _charMap.find(pattern);
            colorChosen = static_cast<int>(it->second);
            if (it != _charMap.end()) {
                attron(COLOR_PAIR(colorChosen));
                mvprintw(x + index, y, "  ");
            }
        }
    }

}

arcade::KeyPressed arcade::NCurses::checkKeyPressed(int key)
{
    if (key == KEY_UP)
        return UP;
    if (key == KEY_DOWN)
        return DOWN;
    if (key == KEY_LEFT)
        return LEFT;
    if (key == KEY_RIGHT)
        return RIGHT;
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
