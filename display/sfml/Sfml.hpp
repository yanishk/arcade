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
            Sfml() = default;
            ~Sfml() = default;

            void init(std::map<std::string, std::string> pattern) override;
            void stop() override;
            bool game(std::array<std::string, 19> map) override;
            void displayText(std::vector<std::string>) override;
            void displayMap(std::array<std::string, 19> map) override;
            arcade::KeyPressed getKey() override;
            void setKey(arcade::KeyPressed newValue) override;
            void pickColor(std::map<std::string, std::string> patternMap);
            void initRectShape(std::string pattern, sf::Color color, int posX, int posY);
            arcade::KeyPressed checkKeyPressed(sf::Event event);
            void initWindow();

        protected:
        private:
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
