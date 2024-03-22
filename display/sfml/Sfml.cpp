/*
** EPITECH PROJECT, 2024
** acd
** File description:
** Sfml
*/

#include "Sfml.hpp"

void arcade::Sfml::initWindow()
{
    _window.create(sf::VideoMode(1000, 1000), "SFML", sf::Style::Default);
}

void arcade::Sfml::init(std::map<std::string, std::string> pattern)
{
    initWindow();
    pickColor(pattern);
    if (!_font.loadFromFile("display/sfml/asset/font/OpenSans-Regular.ttf"))
        exit(84);
}

void arcade::Sfml::pickColor(std::map<std::string, std::string> patternMap)
{
    int posX = 0;
    int posY = 0;

    for (auto it = patternMap.begin(); it != patternMap.end(); it++) {
        if (it->second == "Black") {
            initRectShape(it->first, sf::Color::Black, posX, posY);
        }
        if (it->second == "White"){
            initRectShape(it->first, sf::Color::White, posX, posY);
        }
        if (it->second == "Red") {
            initRectShape(it->first, sf::Color::Red, posX, posY);
        }
        if (it->second == "Blue") {
            initRectShape(it->first, sf::Color::Blue, posX, posY);
        }
        if (it->second == "Green") {
            initRectShape(it->first, sf::Color::Green, posX, posY);
        }
        if (it->second == "Yellow") {
            initRectShape(it->first, sf::Color::Yellow, posX, posY);
        }
        posX += 10;
        posY += 10;
    }
}

void arcade::Sfml::displayRectMap(std::array<std::string, 19> map)
{
    size_t y = 0;
    std::string hay;
    int xPos = 50;
    int yPos = 0;

    for (size_t x = 0; x != 19; x += 1) {
        while (y != 38) {
            hay = std::string(1, map[x][y]) + std::string(1, map[x][y+1]);
            auto it = _charMap.find(hay);
            if (it != _charMap.end()) {
                it->second.setPosition(yPos, xPos);
                _window.draw(it->second);
            }
            yPos += 50;
            y += 2;
        }
        yPos = 0;
        xPos += 50;
        y = 0;
    }
}

void arcade::Sfml::displayText(std::vector<std::string> textToDisplay)
{
    sf::Text text;

    for (auto it : textToDisplay) {
        text.setFont(_font);
        text.setString(it);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        _window.draw(text);
    }
}

void arcade::Sfml::initRectShape(std::string pattern, sf::Color color, int posX, int posY)
{
    sf::RectangleShape rect;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posY, posX);
    rect.setFillColor(color);

    _charMap[pattern] = rect;
}

bool arcade::Sfml::game(std::array<std::string, 19> map)
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return true;
        if (event.type == sf::Event::KeyPressed) {
            _key = checkKeyPressed(event);
        }
    }
    displayRectMap(map);
    _window.display();
    _window.clear();
    return false;
}

void arcade::Sfml::setKey(arcade::KeyPressed newValue)
{
    _key = newValue;
}

arcade::KeyPressed arcade::Sfml::checkKeyPressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Up)
        return KeyPressed::UP;
    if (event.key.code == sf::Keyboard::Down)
        return KeyPressed::DOWN;
    if (event.key.code == sf::Keyboard::Left)
        return KeyPressed::LEFT;
    if (event.key.code == sf::Keyboard::Right)
        return KeyPressed::RIGHT;
    return KeyPressed::OTHER;
}

arcade::KeyPressed arcade::Sfml::getKey()
{
    return _key;
}

void arcade::Sfml::stop()
{
    _window.close();
}