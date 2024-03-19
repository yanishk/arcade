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
            Core(std::string libPath, std::string gamePath);
            ~Core() {};

            void initLoop(void);
            void setExit(bool exit);
            std::pair<arcade::IDisplayModule *, void *> openLib(std::string path);
            std::pair<arcade::IGameModule *, void *> openGame(std::string path);
        private:
            std::vector<std::pair<arcade::IGameModule *, void *>> _game;
            std::vector<std::pair<arcade::IDisplayModule *, void *>> _lib;
            bool _exit;
    };
}

#endif /* !CORE_HPP_ */
