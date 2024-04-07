/*
** EPITECH PROJECT, 2024
** acd
** File description:
** Sfml
*/

#include "Sfml.hpp"
#include "Error.hpp"
#include <iostream>

void arcade::Sfml::initWindow() noexcept
{
    _window.create(sf::VideoMode(1920, 1080), "SFML", sf::Style::Default);
}

void arcade::Sfml::init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern)
{
    initWindow();
    if (!_font.loadFromFile("assets/font/OpenSans-Regular.ttf"))
        throw arcade::Error("Font not found");
    _spriteLoaded = 0;
    pickColor(pattern);
}

void arcade::Sfml::changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap) noexcept
{
    pickColor(patternMap);
}

void arcade::Sfml::initRectShape(const std::string pattern, const sf::Color color, const int posX, const int posY) noexcept
{
    sf::RectangleShape rect;

    rect.setSize(sf::Vector2f(40, 40));
    rect.setPosition(posY, posX);
    rect.setFillColor(color);
    _charMap[pattern].first = rect;
}

void arcade::Sfml::initSprite(const std::string pattern, const int posX, const int posY, const std::string pathFile)
{
    static sf::Texture texture;
    static sf::Sprite sprite;
    static struct _spriteStruct s = { texture, sprite };

    _spriteVector.push_back(s);
    if (!_spriteVector[_spriteLoaded]._texture.loadFromFile(pathFile))
        throw arcade::Error("Sprite not found");
    _spriteVector[_spriteLoaded]._sprite.setTexture(_spriteVector[_spriteLoaded]._texture);
    _spriteVector[_spriteLoaded]._sprite.setPosition(posY, posX);
    _charMap[pattern].second = _spriteVector[_spriteLoaded]._sprite;
    _spriteLoaded += 1;
}


void arcade::Sfml::pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap)
{
    int posX = 0;
    int posY = 0;

    if (_spriteLoaded != 0) {
        _spriteLoaded = 0;
        _spriteVector.clear();
    }

    for (auto it = patternMap.begin(); it != patternMap.end(); it++) {
        if (it->second.first == BLACK) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::Black, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == WHITE) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::White, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == RED) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::Red, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == BLUE) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::Blue, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == GREEN) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::Green, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == YELLOW) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::Yellow, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == CYAN) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color::Cyan, posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        if (it->second.first == GRAY) {
            if (it->second.second.empty())
                initRectShape(it->first, sf::Color(150, 150, 150), posX, posY);
            else
                initSprite(it->first, posX, posY, it->second.second);
        }
        posX += 10;
        posY += 10;
    }
}

void arcade::Sfml::displayMap(const std::array<std::string, 23> map, const std::size_t size) noexcept
{
    std::size_t y = 0;
    std::string hay;
    int xPos = 50;
    int yPos = 0;

    for (std::size_t x = 0; x != map.size(); x += 1) {
        while (y != map[0].size()) {
            if (size == 2)
                hay = std::string(1, map[x][y]) + std::string(1, map[x][y+1]);
            else
                hay = std::string(1, map[x][y]);
            auto it = _charMap.find(hay);
            if (it != _charMap.end()) {
               it->second.first.setPosition(yPos, xPos);
                it->second.second.setPosition(yPos, xPos);
                _window.draw(it->second.first);
                _window.draw(it->second.second);
            }
            yPos += 40;
            y += size;
        }
        yPos = 0;
        xPos += 40;
        y = 0;
    }

}

void arcade::Sfml::displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) noexcept
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

void arcade::Sfml::displayPlayerName(const std::string gameName) noexcept
{
    sf::Text text;

    if (gameName != "Menu")
        return;
    text.setFont(_font);
    text.setString("Player name: " + _playerName);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    _window.draw(text);
}

void arcade::Sfml::savePlayerName(const sf::Event event) noexcept
{
    if (event.text.unicode < 128 && isKeyAccepted(_key))
        _playerName += static_cast<char>(event.text.unicode);
}

bool arcade::Sfml::isKeyAccepted(const KeyPressed key) const noexcept
{
    return (key != UP && key != DOWN && key != LEFT && key != RIGHT && key != ENTER);
}

void arcade::Sfml::handleEvent(const std::string gameName) noexcept
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _key = CLOSE_BUTTON;
        if (event.type == sf::Event::KeyPressed)
            _key = checkKeyPressed(event);
        if (gameName == "Menu" && event.type == sf::Event::TextEntered)
            savePlayerName(event);
    }
    displayPlayerName(gameName);
    _window.display();
    _window.clear();
}

void arcade::Sfml::setKey(const arcade::KeyPressed newValue) noexcept
{
    _key = newValue;
}

arcade::KeyPressed arcade::Sfml::checkKeyPressed(const sf::Event event) const noexcept
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
    if (event.key.code == sf::Keyboard::M)
        return M;
    if (event.key.code == sf::Keyboard::Enter)
        return ENTER;
    return OTHER;
}

arcade::KeyPressed arcade::Sfml::getKey() const noexcept
{
    return _key;
}

std::string arcade::Sfml::getPlayerName() const noexcept
{
    return _playerName;
}

void arcade::Sfml::stop() noexcept
{
    _charMap.clear();
    _spriteVector.clear();
    _spriteLoaded = 0;
    _window.close();
}