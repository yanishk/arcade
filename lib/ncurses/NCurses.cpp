/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"

void arcade::NCurses::init()
{
    initscr();
    noecho();
    _window = newwin(15, 17, 2, 10);
}

void arcade::NCurses::stop()
{
    endwin();
}

bool arcade::NCurses::game()
{
    char c;

    while (c != 27) {
        box(_window, 0, 0);
        mvwprintw(_window, 1, 1, "Arcade\n");
        wrefresh(_window);
        c = getch();
    }
    return true;
}

void arcade::NCurses::playerNameDisplay(const std::string displayText)
{
    mvprintw(100, 80, "%s\n", displayText.c_str());
}

const std::string &arcade::NCurses::getName() const
{
    return _name;
}