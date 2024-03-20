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
    char c;

    while (c != 27) {
        mvprintw(0, 0, "Arcade\n");
        displayMap(map);
        wrefresh(_window);
        c = getch();
    }
    return true;
}

void arcade::NCurses::textDisplay(const std::string displayText, int xPos, int yPos)
{
    mvprintw(xPos, yPos, "%s\n", displayText.c_str());
}

void arcade::NCurses::displayMap(std::array<std::string, 19> map)
{
    for (int i = 0; i != 19; i += 1)
        mvprintw(0, 0, "%s\n", map[i]);
}
