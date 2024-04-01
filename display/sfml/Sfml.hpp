/*
** EPITECH PROJECT, 2024
** acd
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IDisplayModule.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

namespace arcade
{
    class Sfml : virtual public IDisplayModule
    {
        public:
            Sfml() : _key(OTHER) {};
            ~Sfml() = default;

            void init(const std::unordered_map<std::string, Color> pattern) override;
            void stop() noexcept override;
            void game(const std::string gameName) noexcept override;
            void changeColor(const std::unordered_map<std::string, Color> patternMap) noexcept override;
            void displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) noexcept override;
            void displayMap(const std::array<std::string, 23> map, const std::size_t size) noexcept override;
            KeyPressed getKey() const noexcept override;
            void setKey(const KeyPressed newValue) noexcept override;
            std::string getPlayerName() const noexcept override;

        private:
            void initWindow() noexcept;
            void pickColor(const std::unordered_map<std::string, Color> patternMap) noexcept;
            void initRectShape(const std::string pattern, const sf::Color color, const int posX, const int posY) noexcept;
            KeyPressed checkKeyPressed(const sf::Event event) const noexcept;
            void savePlayerName(const sf::Event event) noexcept;
            void displayPlayerName(const std::string gameName) noexcept;
            std::unordered_map<std::string, sf::RectangleShape> _charMap;
            sf::RenderWindow _window;
            KeyPressed _key;
            sf::Font _font;
            std::string _playerName;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::Sfml;
    }
}


#endif /* !SFML_HPP_ */
