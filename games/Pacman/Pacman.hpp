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

            void resetGame() noexcept;
            std::string getGameName() const noexcept override;
            std::size_t getScore() const noexcept override;
            std::array<std::string, 23> getMap() const noexcept override;
            std::size_t getMapCellSize() const noexcept override;
            std::unordered_map<std::string, Color> getPattern() const noexcept override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const noexcept override;
            void incrementTime() noexcept override;
            GameStatus updateMap(KeyPressed key) noexcept override;
            std::pair<std::size_t, std::size_t> getIndexes() const noexcept override;
            void keyEnter(const KeyPressed) noexcept override {};
            void initText(const std::vector<std::string>, const std::vector<std::string>) noexcept override {};

        private:
            std::pair<std::size_t, std::size_t> getPos(char c,
                const std::array<std::string, 23> map) const noexcept;
            std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>> getGhostsPos() const noexcept;
            GameStatus checkGhostUp(const std::size_t x, const std::size_t y) noexcept;
            GameStatus checkGhostDown(const std::size_t x, const std::size_t y) noexcept;
            GameStatus checkGhostLeft(const std::size_t x, const std::size_t y) noexcept;
            GameStatus checkGhostRight(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goUp(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goDown(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goLeft(const std::size_t x, const std::size_t y) noexcept;
            GameStatus goRight(const std::size_t x, const std::size_t y) noexcept;
            GameStatus ghostGoUp(std::size_t &x, std::size_t &y, char &previousChar, const int ghostIndex) noexcept;
            GameStatus ghostGoDown(std::size_t &x, std::size_t &y, char &previousChar, const int ghostIndex) noexcept;
            GameStatus ghostGoLeft(std::size_t &x, std::size_t &y, char &previousChar, const int ghostIndex) noexcept;
            GameStatus ghostGoRight(std::size_t &x, std::size_t &y, char &previousChar, const int ghostIndex) noexcept;
            GameStatus restartGame(KeyPressed &lastKey) noexcept;
            GameStatus checkGhostDirections(const std::size_t i) noexcept;
            GameStatus getOutOfBox() noexcept;
            GameStatus moveGhosts() noexcept;
            GameStatus manageGhosts() noexcept;
            GameStatus manageKeys(KeyPressed &key, KeyPressed &lastKey) noexcept;
            Food whichFood(const char c) noexcept;
            void impulsePacman(KeyPressed &key, KeyPressed &lastKey) noexcept;
            void increaseScore(const Food foodType) noexcept;
            void setGhostsColor() noexcept;
            void resetGhostPosition(const std::size_t i) noexcept;
            bool isLittleFood(const char c) const noexcept;
            bool isBigFood(const char c) const noexcept;
            bool isAvailableForPlayer(const char c) const noexcept;
            bool isAvailableForGhost(const char c) const noexcept;
            bool isGhost(const char c) const noexcept;
            bool isPlayer(const char c) const noexcept;
            bool checkWin() const noexcept;
            std::array<std::string, 23> _defaultMap;
            std::array<std::string, 23> _map;
            std::unordered_map<std::string, Color> _patternPath;
            std::size_t _sizeCell;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>> _defaultGhostsPos;
            std::vector<std::pair<char,std::pair<std::size_t, std::size_t>>> _ghostsPos;
            std::vector<std::size_t> _jailTime;
            std::string _gameName;
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
