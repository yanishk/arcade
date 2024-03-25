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
    class Menu : virtual public IGameModule {
        public:
            Menu()= default ;
            ~Menu() = default;

            void resetGame() override {};
            std::array<std::string, 21> getMap() override {};
            std::map<std::string, Color> getPattern() override {};
            std::vector<std::string> getText()  override {};
            GameStatus updateMap(arcade::KeyPressed key) override {};
            KeyPressed nextPlayerMove() override {};
            std::size_t getSize() override {};
        protected:
        private:
            std::vector<std::string> _textToDisplay;
    };
}

#endif /* !MENU_HPP_ */
