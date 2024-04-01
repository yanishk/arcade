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

            void resetGame() noexcept override;
            std::string getGameName() const noexcept override;
            std::size_t getScore() const noexcept override;
            std::array<std::string, 23> getMap() const noexcept override;
            std::unordered_map<std::string, Color> getPattern() const noexcept override;
            std::size_t getMapCellSize() const noexcept override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const noexcept override;
            void incrementTime() noexcept override;
            GameStatus updateMap(KeyPressed key) noexcept override;
            std::pair<std::size_t, std::size_t> getIndexes() const noexcept override;
            void keyEnter(const KeyPressed key) noexcept override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) noexcept override;

        private:
            void keyDown() noexcept;
            void keyUp() noexcept;
            std::vector<std::pair<std::string, std::pair<int, int>>> _textToDisplay;
            std::array<std::string, 23> _map;
            std::unordered_map<std::string, Color> _patternPath;
            std::string _gameName;
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
