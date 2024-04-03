/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGameModule.hpp"

namespace arcade
{
    class Nibbler : virtual public IGameModule
    {
        public :
            Nibbler();
            ~Nibbler() = default;

            void resetGame() noexcept override;
            std::string getGameName() const noexcept override;
            std::size_t getScore() const noexcept override;
            std::array<std::string, 23> getMap() const noexcept override;
            std::size_t getMapCellSize() const noexcept override;
            std::unordered_map<std::string, std::pair<Color, std::string>> getPattern() const noexcept override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const noexcept override;
            void incrementTime() noexcept override;
            GameStatus updateMap(KeyPressed key) noexcept override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) noexcept override {};
            std::pair<std::size_t, std::size_t> getIndexes() const noexcept override;

        private:
            GameStatus goUp(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goDown(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goLeft(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goRight(const std::size_t x, const std::size_t y) noexcept;
            void stockPlayerPos() noexcept;
            std::pair<std::size_t, std::size_t> getPlayerHeadPos() const noexcept;
            void updatePlayerPos(const std::pair <std::size_t, std::size_t> newCell1,
                const std::pair <std::size_t, std::size_t> newCell2,
                const std::pair<std::size_t, std::size_t> playerHead) noexcept;
            void increaseScore() noexcept;
            void growSnakeTail(const std::pair <std::size_t, std::size_t> snakeTailCell1,
                const std::pair <std::size_t, std::size_t> snakeTailCell2) noexcept;
            bool isAvailable(const char c) const noexcept;
            bool isFood(const char firstChar, const char secondChar) const noexcept;
            bool isSnakeBody(const char firstChar, const char secondChar) const noexcept;
            bool isNeckPattern1(const std::pair <std::size_t, std::size_t> cell1,
                    const std::pair <std::size_t, std::size_t> cell2) const noexcept;
            bool isNeckPattern2(const std::pair <std::size_t, std::size_t> cell1,
                const std::pair <std::size_t, std::size_t> cell2) const noexcept;
            bool isSnakeNeck(const std::pair <std::size_t, std::size_t> cell1,
                const std::pair <std::size_t, std::size_t> cell2) const noexcept;
            bool checkLoose(const std::pair <std::size_t, std::size_t> cell1,
                const std::pair <std::size_t, std::size_t> cell2) const noexcept;
            bool checkWin() const noexcept;
            bool isTJunction(const std::size_t x, const std::size_t y) const noexcept;
            bool isTJunctionUp(const std::size_t x, const std::size_t y) const noexcept;
            bool isTJunctionDown(const std::size_t x, const std::size_t y) const noexcept;
            bool isTJunctionRight(const std::size_t x, const std::size_t y) const noexcept;
            bool isTJunctionLeft(const std::size_t x, const std::size_t y) const noexcept;
            GameStatus nextPlayerMove() noexcept;
            GameStatus checkRightCell(const std::size_t x, const std::size_t y,
            KeyPressed &lastMove) noexcept;
            GameStatus checkUpCell(const std::size_t x, const std::size_t y,
            KeyPressed &lastMove) noexcept;
            GameStatus checkLeftCell(const std::size_t x, const std::size_t y,
            KeyPressed &lastMove) noexcept;
            GameStatus checkDownCell(const std::size_t x, const std::size_t y,
            KeyPressed &lastMove) noexcept;
            GameStatus checkMovingPlayer(const arcade::KeyPressed
            lastMove, const std::size_t x, const std::size_t y) noexcept;
            GameStatus movingPlayerRight(const std::size_t x, const std::size_t y) noexcept;
            GameStatus movingPlayerUp(const std::size_t x, const std::size_t y) noexcept;
            GameStatus movingPlayerLeft(const std::size_t x, const std::size_t y) noexcept;
            GameStatus movingPlayerDown(const std::size_t x, const std::size_t y) noexcept;
            std::array<std::string, 23> _defaultMap;
            std::array<std::string, 23> _map;
            std::unordered_map<std::string, std::pair<Color, std::string>> _patternPath;
            std::size_t _sizeCell;
            std::vector <std::pair<std::size_t, std::size_t>> _snakePos;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::string _scoreText;
            std::size_t _score;
            std::size_t _time;
            std::string _gameName;
    };
}

extern "C"
{
    arcade::Nibbler* entryPoint() {
        return new arcade::Nibbler;
    }
}

#endif /* !NIBBLER_HPP_ */
