/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"

void arcade::NCurses::init(std::map<std::string, std::string>)
{
    initscr();
    noecho();
    _window = newwin(15, 17, 2, 10);
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
        wrefresh(_window);
        key = getch();
        if (key == 27)
            return true;
        _key = checkKeyPressed(key);
    return false;
}

void arcade::NCurses::textDisplay(const std::string displayText, int xPos, int yPos)
{
    mvprintw(xPos, yPos, "%s\n", displayText.c_str());
}

void arcade::NCurses::displayMap(std::array<std::string, 19> map)
{
    for (int i = 0; i != 19; i += 1)
        mvprintw(i, 0, "%s\n", map[i].c_str());
}

arcade::KeyPressed arcade::NCurses::checkKeyPressed(int key)
{
    if (key == KEY_UP)
        return KeyPressed::UP;
    if (key == KEY_DOWN)
        return KeyPressed::DOWN;
    if (key == KEY_LEFT)
        return KeyPressed::LEFT;
    if (key == KEY_RIGHT)
        return KeyPressed::RIGHT;
    return KeyPressed::OTHER;
}

void arcade::NCurses::setKey(arcade::KeyPressed newValue)
{
    _key = newValue;
}

arcade::KeyPressed arcade::NCurses::getKey()
{
    return _key;
}
