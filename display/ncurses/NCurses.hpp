/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

#include "IDisplayModule.hpp"
#include <ncurses.h>

namespace arcade
{
    class NCurses : virtual public IDisplayModule
    {
        public:
            NCurses() : _key(OTHER) {};
            ~NCurses() = default;

            void init(const std::unordered_map<std::string, std::pair<Color, std::string>> pattern) noexcept override;
            void stop() noexcept override;
            void handleEvent(const std::string gameName) noexcept override;
            void changeColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap) noexcept override;
            void displayText(const std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) noexcept override;
            void displayMap(const std::array<std::string, 23> map, const std::size_t size) noexcept override;
            KeyPressed getKey() const noexcept override;
            void setKey(const KeyPressed newValue) noexcept override;
            std::string getPlayerName() const noexcept override;

        private:
            void pickColor(const std::unordered_map<std::string, std::pair<Color, std::string>> patternMap) noexcept;
            void savePlayerName(const std::string gameName) noexcept;
            KeyPressed checkKeyPressed(const unsigned int key) const noexcept;
            KeyPressed _key;
            WINDOW *_window;
            std::string _playerName;
            std::unordered_map<std::string, std::pair<Color, std::string>> _charMap;
    };
}

extern "C"
{
    arcade::IDisplayModule* entryPoint() {
        return new arcade::NCurses;
    }
}

#endif /* !NCURSES_HPP_ */
