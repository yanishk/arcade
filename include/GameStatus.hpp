/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** GameStatus
*/

#ifndef GAMESTATUS_HPP_
#define GAMESTATUS_HPP_

namespace arcade
{
    enum GameStatus
    {
        PLAYING,
        WON,
        WON_AND_RELOADED,
        LOOSE,
        QUIT,
        NO_ACTIVITY,
        MENU
    };
}

#endif /* !GAMESTATUS_HPP_ */
