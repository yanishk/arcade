/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGameModule.hpp"

namespace arcade
{
    class Pacman : virtual public IGameModule
    {
        public:

            enum Food
            {
                NOTAFOOD,
                LITTLEFOOD,
                BIGFOOD
            };

            Pacman();
            ~Pacman() = default;

            void resetGame();
            std::array<std::string, 23> getMap() override;
            std::size_t getMapCellSize() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            void incrementTime() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() override;
            void keyEnter(arcade::KeyPressed) override {};
            void initText(std::vector<std::string>, std::vector<std::string>) override {};

        private:
            std::pair<std::size_t, std::size_t> getPos(char c,
                std::array<std::string, 23> map);
            std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>> getGhostsPos();
            GameStatus checkGhostUp(std::size_t x, std::size_t y);
            GameStatus checkGhostDown(std::size_t x, std::size_t y);
            GameStatus checkGhostLeft(std::size_t x, std::size_t y);
            GameStatus checkGhostRight(std::size_t x, std::size_t y);
            GameStatus goUp(std::size_t x, std::size_t y);
            GameStatus goDown(std::size_t x, std::size_t y);
            GameStatus goLeft(std::size_t x, std::size_t y);
            GameStatus goRight(std::size_t x, std::size_t y);
            GameStatus ghostGoUp(std::size_t &x, std::size_t &y, char &previousChar, int ghostIndex);
            GameStatus ghostGoDown(std::size_t &x, std::size_t &y, char &previousChar, int ghostIndex);
            GameStatus ghostGoLeft(std::size_t &x, std::size_t &y, char &previousChar, int ghostIndex);
            GameStatus ghostGoRight(std::size_t &x, std::size_t &y, char &previousChar, int ghostIndex);
            GameStatus restartGame(KeyPressed &lastKey);
            GameStatus checkGhostDirections(std::size_t i);
            GameStatus getOutOfBox();
            GameStatus moveGhosts();
            GameStatus manageGhosts();
            GameStatus manageKeys(KeyPressed &key, KeyPressed &lastKey);
            Food whichFood(char c);
            void impulsePacman(KeyPressed &key, KeyPressed &lastKey);
            void increaseScore(Food foodType);
            void setGhostsColor();
            void resetGhostPosition(std::size_t i);
            bool isLittleFood(char c);
            bool isBigFood(char c);
            bool isAvailableForPlayer(char c);
            bool isAvailableForGhost(char c);
            bool isGhost(char c);
            bool isPlayer(char c);
            bool checkWin();
            std::array<std::string, 23> _defaultMap;
            std::array<std::string, 23> _map;
            std::map<std::string, Color> _patternPath;
            std::size_t _sizeCell;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>> _defaultGhostsPos;
            std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>> _ghostsPos;
            std::vector<std::size_t> _jailTime;
            std::string _scoreText;
            std::size_t _score;
            std::size_t _time;
            std::size_t _turn;
            bool _canEatGhosts;
            std::vector<bool> _firstExit;
            std::vector<bool> _ghostsCanChase;
    };
}

extern "C"
{
    arcade::Pacman* entryPoint() {
        return new arcade::Pacman;
    }
}

#endif /* !PACMAN_HPP_ */
