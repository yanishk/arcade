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
    class Sfml : virtual public IDisplayModule {
        public:
            Sfml() : _key(OTHER) {};
            ~Sfml() = default;

            void init(std::map<std::string, Color> pattern) override;
            void stop() override;
            void game() override;
            void displayText(std::vector<std::string> textToDisplay) override;
            void displayMap(std::array<std::string, 21> map, std::size_t size) override;
            arcade::KeyPressed getKey() override;
            void setKey(arcade::KeyPressed newValue) override;
            void pickColor(std::map<std::string, Color> patternMap) override;

        private:
            void initRectShape(std::string pattern, sf::Color color, int posX, int posY);
            void initWindow();
            arcade::KeyPressed checkKeyPressed(sf::Event event);
            std::map<std::string, sf::RectangleShape> _charMap;
            sf::RenderWindow _window;
            KeyPressed _key;
            sf::Font _font;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::Sfml;
    }
}


#endif /* !SFML_HPP_ */
