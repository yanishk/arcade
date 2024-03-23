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
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

namespace arcade
{
    class Core
    {
        public:
            Core(std::string libPath);
            ~Core() = default;

            void initLoop();
            void setExit(bool exit);
            arcade::IDisplayModule *openLib(std::string path);
            arcade::IGameModule *openGame(std::string path);
        private:
            std::vector<arcade::IGameModule *> _game;
            std::vector<arcade::IDisplayModule *> _lib;
            bool _exit;
    };
}

#endif /* !CORE_HPP_ */
