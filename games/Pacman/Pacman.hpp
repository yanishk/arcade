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
    class Pacman : virtual public IGameModule {
        public:
            Pacman();
            ~Pacman() = default;

            void resetGame() override {};
            std::array<std::string, 21> getMap() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::string> getText() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            KeyPressed nextPlayerMove() override { return OTHER; };
            std::size_t getSize() override;

        protected:
        private:
            std::array<std::string, 21> _defaultMap;
            std::array<std::string, 21> _map;
            std::map<std::string, Color> _patternPath;
            std::size_t _sizeCell;
            std::vector<std::string> _textToDisplay;
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
