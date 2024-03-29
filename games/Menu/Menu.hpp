/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "IGameModule.hpp"

namespace arcade
{
    class Menu : virtual public IGameModule
    {
        public:
            Menu();
            ~Menu() = default;

            void resetGame() override {};
            std::array<std::string, 23> getMap() override;
            std::map<std::string, Color> getPattern() override;
            std::size_t getMapCellSize() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            void incrementTime() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() override;
            void keyEnter(arcade::KeyPressed key) override;
            void initText(std::vector<std::string>, std::vector<std::string>) override;

        private:
            void keyDown();
            void keyUp();
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::array<std::string, 23> _map;
            std::map<std::string, arcade::Color> _patternPath;
            std::size_t _sizeCell;
            std::size_t _time;
            bool _libSelected;
            bool _gameSelected;
            std::size_t _selectLibArrow;
            std::size_t _selectGameArrow;
            std::size_t _indexLib;
            std::size_t _indexGame;

    };
}

extern "C"
{
    arcade::Menu* entryPoint() {
        return new arcade::Menu;
    }
}

#endif /* !MENU_HPP_ */
