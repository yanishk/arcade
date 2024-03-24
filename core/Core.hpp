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
            void switchLibrary(std::string libPath);
        private:
            void managePlayerAutoMoves(std::chrono::steady_clock::time_point &clockT0, int index);
            std::vector<arcade::IGameModule *> _game;
            std::vector<arcade::IDisplayModule *> _lib;
            int _curentLib;
            bool _exit;
    };
}

#endif /* !CORE_HPP_ */
