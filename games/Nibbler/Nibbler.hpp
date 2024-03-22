/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGameModule.hpp"
#include <map>

namespace arcade
{
    class Nibbler : virtual public IGameModule
    {
        public :
            Nibbler();
            ~Nibbler() = default;

            std::array<std::string, 19> getMap() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::string> getText() override;
            void updateMap(arcade::KeyPressed key) override;
            void updatePlayerPos() override;
            void stockPlayerPos() override;
            std::pair<std::size_t, std::size_t> getPlayerHeadPos() override;

        private:
            bool checkWin();
            void goUp(std::size_t x, std::size_t y);
            void goDown(std::size_t x, std::size_t y);
            void goLeft(std::size_t x, std::size_t y);
            void goRight(std::size_t x, std::size_t y);
            bool isFree(char c);
            bool isFood(char c);
            bool isSnakeBody(char firstChar, char secondChar);
            bool isNotSnakeNeck(std::size_t x, std::size_t y);
            std::array<std::string, 19> _map;
            std::map<std::string, Color> _patternPath;
            std::vector <std::pair<std::size_t, std::size_t>> _snakePos;
            std::size_t _score;
            std::string _scoreText;
            std::vector<std::string> _textToDisplay;
    };
}

extern "C"
{
    arcade::Nibbler* entryPoint() {
        return new arcade::Nibbler;
    }
}

#endif /* !NIBBLER_HPP_ */
