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
            std::array<std::string, 21> getMap() override;
            std::map<std::string, Color> getPattern() override;
            std::size_t getMapCellSize() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            bool isAvailable(char c) override;
            void keyDown();
            void keyUp();
            void keyEnter();

        private:
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::array<std::string, 21> _map;
            std::map<std::string, arcade::Color> _patternPath;
            std::size_t _sizeCell;
            bool _libSelected;
    };
}

extern "C"
{
    arcade::Menu* entryPoint() {
        return new arcade::Menu;
    }
}

#endif /* !MENU_HPP_ */
