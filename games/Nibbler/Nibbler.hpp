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

            void resetGame() override;
            std::array<std::string, 21> getMap() override;
            std::size_t getMapCellSize() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            GameStatus updateMap(KeyPressed key) override;
            bool isAvailable(char c) override;
            void keyEnter(arcade::KeyPressed) override {};
            void initText(std::vector<std::string>, std::vector<std::string>) override {};
            std::pair<std::size_t, std::size_t> getIndexes() override;

        private:
            GameStatus goUp(std::size_t x, std::size_t y);
            GameStatus goDown(std::size_t x, std::size_t y);
            GameStatus goLeft(std::size_t x, std::size_t y);
            GameStatus goRight(std::size_t x, std::size_t y);
            void stockPlayerPos();
            std::pair<std::size_t, std::size_t> getPlayerHeadPos();
            void updatePlayerPos(std::pair <std::size_t, std::size_t> newCell1,
                std::pair <std::size_t, std::size_t> newCell2,
                std::pair<std::size_t, std::size_t> playerHead);
            void increaseScore();
            void growSnakeTail(std::pair <std::size_t, std::size_t> snakeTailCell1,
                std::pair <std::size_t, std::size_t> snakeTailCell2);
            bool isFood(char firstChar, char secondChar);
            bool isSnakeBody(char firstChar, char secondChar);
            bool isNeckPattern1(std::pair <std::size_t, std::size_t> cell1,
                    std::pair <std::size_t, std::size_t> cell2);
            bool isNeckPattern2(std::pair <std::size_t, std::size_t> cell1,
                std::pair <std::size_t, std::size_t> cell2);
            bool isSnakeNeck(std::pair <std::size_t, std::size_t> cell1,
                std::pair <std::size_t, std::size_t> cell2);
            bool checkLoose(std::pair <std::size_t, std::size_t> cell1,
                std::pair <std::size_t, std::size_t> cell2);
            bool checkWin();
            bool isTJunction(std::size_t x,  std::size_t y);
            bool isTJunctionUp(std::size_t x,  std::size_t y);
            bool isTJunctionDown(std::size_t x,  std::size_t y);
            bool isTJunctionRight(std::size_t x,  std::size_t y);
            bool isTJunctionLeft(std::size_t x,  std::size_t y);
            GameStatus nextPlayerMove();
            GameStatus checkRightCell(std::size_t x, std::size_t y,
            KeyPressed &lastMove);
            GameStatus checkUpCell(std::size_t x, std::size_t y,
            KeyPressed &lastMove);
            GameStatus checkLeftCell(std::size_t x, std::size_t y,
            KeyPressed &lastMove);
            GameStatus checkDownCell(std::size_t x, std::size_t y,
            KeyPressed &lastMove);
            GameStatus checkMovingPlayer(arcade::KeyPressed
            lastMove, std::size_t x, std::size_t y);
            GameStatus movingPlayerRight(std::size_t x, std::size_t y);
            GameStatus movingPlayerUp(std::size_t x, std::size_t y);
            GameStatus movingPlayerLeft(std::size_t x, std::size_t y);
            GameStatus movingPlayerDown(std::size_t x, std::size_t y);
            std::array<std::string, 21> _defaultMap;
            std::array<std::string, 21> _map;
            std::map<std::string, Color> _patternPath;
            std::size_t _sizeCell;
            std::vector <std::pair<std::size_t, std::size_t>> _snakePos;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::string _scoreText;
            std::size_t _score;
    };
}

extern "C"
{
    arcade::Nibbler* entryPoint() {
        return new arcade::Nibbler;
    }
}

#endif /* !NIBBLER_HPP_ */
