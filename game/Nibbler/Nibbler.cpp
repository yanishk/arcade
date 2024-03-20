/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#include "Nibbler.hpp"

arcade::Nibbler::Nibbler()
{
    _map = {
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
        "##          <=========8~            ##",
        "######################################"
    };
    _patternPath["##"] = "White";
    _patternPath["  "] = "Black";
    _patternPath["[]"] = "Red";
    _patternPath["=="] = "Blue";
    _patternPath["8~"] = "Green";
    _patternPath["<="] = "Yellow";
}

std::array<std::string, 19> arcade::Nibbler::getMap()
{
    return _map;
}

std::map<std::string, std::string> arcade::Nibbler::getPattern()
{
    return _patternPath;
}

