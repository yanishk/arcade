/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGameModule.hpp"
#include "KeyPressed.hpp"

namespace arcade
{
    class Pacman : virtual public IGameModule
    {
        public:

            enum FOOD
            {
                NOTAFOOD,
                LITTLEFOOD,
                BIGFOOD
            };

            Pacman();
            ~Pacman() = default;

            void resetGame();
            std::array<std::string, 21> getMap() override;
            std::size_t getMapCellSize() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            bool isAvailable(char c) override;
            void keyEnter(arcade::KeyPressed key) override {};
            void initText(std::vector<std::string>, std::vector<std::string>) override {};
            std::pair<std::size_t, std::size_t> getIndexes() override {};

        private:
            std::pair<std::size_t, std::size_t> getPlayerPos();
            GameStatus goUp(std::size_t x, std::size_t y);
            GameStatus goDown(std::size_t x, std::size_t y);
            GameStatus goLeft(std::size_t x, std::size_t y);
            GameStatus goRight(std::size_t x, std::size_t y);
            bool isLittleFood(char c);
            bool isBigFood(char c);
            arcade::Pacman::FOOD whichFood(char c);
            void increaseScore(FOOD foodType);
            bool checkWin();
            std::array<std::string, 21> _defaultMap;
            std::array<std::string, 21> _map;
            std::map<std::string, Color> _patternPath;
            std::size_t _sizeCell;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::string _scoreText;
            std::size_t _score;
    };
}

extern "C"
{
    arcade::Pacman* entryPoint() {
        return new arcade::Pacman;
    }
}

#endif /* !PACMAN_HPP_ */
