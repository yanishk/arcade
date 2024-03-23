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
        " #.######.#.######.# "
    };
    _map = _defaultMap;
    _patternPath["#"] = BLUE;
    _patternPath[" "] = BLACK;
    _patternPath["."] = WHITE;
    _patternPath["!"] = RED;
    _patternPath["P"] = YELLOW;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(_scoreText);
    _sizeMap = 1;

}

std::map<std::string, arcade::Color> arcade::Pacman::getPattern()
{
    return _patternPath;
}

std::size_t arcade::Pacman::getSize()
{
    return _sizeMap;
}

std::vector<std::string> arcade::Pacman::getText()
{
    return _textToDisplay;
}

bool arcade::Pacman::updateMap(arcade::KeyPressed key)
{
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return true;
    return false;
}

std::array<std::string, 19> arcade::Pacman::getMap()
{
    return _map;
}
