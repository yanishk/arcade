/*
** EPITECH PROJECT, 2024
** acd
** File description:
** Sfml
*/

#include "Sfml.hpp"

void arcade::Sfml::initWindow()
{
    _window.create(sf::VideoMode(1080, 1920), "SFML", sf::Style::Default);
}

void arcade::Sfml::init(std::map<std::string, Color> pattern)
{
    initWindow();
    pickColor(pattern);
    if (!_font.loadFromFile("display/sfml/asset/font/OpenSans-Regular.ttf"))
        exit(84);
}

void arcade::Sfml::pickColor(std::map<std::string, Color> patternMap)
{
    int posX = 0;
    int posY = 0;

    for (auto it = patternMap.begin(); it != patternMap.end(); it++) {
        if (it->second == BLACK) {
            initRectShape(it->first, sf::Color::Black, posX, posY);
        }
        if (it->second == WHITE){
            initRectShape(it->first, sf::Color::White, posX, posY);
        }
        if (it->second == RED) {
            initRectShape(it->first, sf::Color::Red, posX, posY);
        }
        if (it->second == BLUE) {
            initRectShape(it->first, sf::Color::Blue, posX, posY);
        }
        if (it->second == GREEN) {
            initRectShape(it->first, sf::Color::Green, posX, posY);
        }
        if (it->second == YELLOW) {
            initRectShape(it->first, sf::Color::Yellow, posX, posY);
        }
        posX += 10;
        posY += 10;
    }
}

void arcade::Sfml::displayMap(std::array<std::string, 21> map, std::size_t size)
{
    size_t y = 0;
    std::string hay;
    int xPos = 50;
    int yPos = 0;

    for (size_t x = 0; x != map.size(); x += 1) {
        while (y != map[0].size()) {
            if (size == 2)
                hay = std::string(1, map[x][y]) + std::string(1, map[x][y+1]);
            else
                hay = std::string(1, map[x][y]);
            auto it = _charMap.find(hay);
            if (it != _charMap.end()) {
                it->second.setPosition(yPos, xPos);
                _window.draw(it->second);
            }
            yPos += 40;
            y += size;
        }
        yPos = 0;
        xPos += 40;
        y = 0;
    }
}

void arcade::Sfml::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    sf::Text text;

    for (auto it : textToDisplay) {
        text.setFont(_font);
        text.setString(it.first);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(it.second.first, it.second.second);
        _window.draw(text);
    }
}

void arcade::Sfml::initRectShape(std::string pattern, sf::Color color, int posX, int posY)
{
    sf::RectangleShape rect;

    rect.setSize(sf::Vector2f(40, 40));
    rect.setPosition(posY, posX);
    rect.setFillColor(color);

    _charMap[pattern] = rect;
}

void arcade::Sfml::game()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _key = CLOSE_BUTTON;
        if (event.type == sf::Event::KeyPressed)
            _key = checkKeyPressed(event);
    }
    _window.display();
    _window.clear();
}

void arcade::Sfml::setKey(arcade::KeyPressed newValue)
{
    _key = newValue;
}

arcade::KeyPressed arcade::Sfml::checkKeyPressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Backspace)
        return BACKSPACE;
    if (event.key.code == sf::Keyboard::Up)
        return UP;
    if (event.key.code == sf::Keyboard::Down)
        return DOWN;
    if (event.key.code == sf::Keyboard::Left)
        return LEFT;
    if (event.key.code == sf::Keyboard::Right)
        return RIGHT;
    if (event.key.code == sf::Keyboard::R)
        return R;
    if (event.key.code == sf::Keyboard::P)
        return P;
    if (event.key.code == sf::Keyboard::N)
        return N;
    if (event.key.code == sf::Keyboard::G)
        return G;
    return OTHER;
}

arcade::KeyPressed arcade::Sfml::getKey()
{
    return _key;
}

void arcade::Sfml::stop()
{
    _window.close();
}