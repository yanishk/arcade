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
        " #.######.#.######.# ",
        " #.................# ",
        " ################### "
    };
    _map = _defaultMap;
    _patternPath["#"] = BLUE;
    _patternPath[" "] = BLACK;
    _patternPath["."] = WHITE;
    _patternPath["!"] = RED;
    _patternPath["P"] = YELLOW;
    _scoreText = "score: " + std::to_string(_score);
    _textToDisplay.push_back(_scoreText);
    _sizeCell = 1;

}

std::map<std::string, arcade::Color> arcade::Pacman::getPattern()
{
    return _patternPath;
}

std::size_t arcade::Pacman::getMapCellSize()
{
    return _sizeCell;
}

std::vector<std::string> arcade::Pacman::getText()
{
    return _textToDisplay;
}

arcade::GameStatus arcade::Pacman::updateMap(arcade::KeyPressed key)
{
    if (key == BACKSPACE || key == CLOSE_BUTTON)
        return QUIT;
    return PLAYING;
}

std::array<std::string, 21> arcade::Pacman::getMap()
{
    return _map;
}
