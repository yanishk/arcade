/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include <vector>
#include <chrono>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

namespace arcade
{
    class Core
    {
        public:
            Core(std::string libPath);
            ~Core() = default;

            void loop();
            arcade::IDisplayModule *openLib(std::string path);
            arcade::IGameModule *openGame(std::string path);

        private:
            void managePlayerAutoMoves(std::chrono::steady_clock::time_point &clockT0, int index);
            size_t manageDynamicSwitchLib(std::size_t indexLib, size_t indexGame);
            size_t manageDynamicSwitchGame(std::size_t indexLib, size_t indexGame);
            void manageMenuSwitchLib(std::size_t indexLib, std::size_t indexGame, std::size_t tmp);
            void manageMenuSwitchGame(std::size_t indexLib, std::size_t indexGame, std::size_t tmp);
            void readLib(std::string libPath);
            void readGame();
            std::vector<arcade::IGameModule *> _game;
            std::vector<arcade::IDisplayModule *> _lib;
            std::vector<std::string> _gameText;
            std::vector<std::string> _libText;
            bool _exit;
            std::array<std::string, 3> _libName;
            std::array<std::string, 3> _gameName;
    };
}

#endif /* !CORE_HPP_ */
