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
#include "DLLoader.hpp"

namespace arcade
{
    class Core
    {
        public:
            Core(const std::string libPath);
            ~Core() = default;

            void loop();

        private:
            void readLib(const std::string libPath);
            void manageMenuSwitchLib(const std::size_t indexLib, const std::size_t indexGame, const std::size_t tmp) const;
            void manageMenuSwitchGame(const std::size_t indexLib, const std::size_t indexGame, const std::size_t tmp) const;
            size_t manageDynamicSwitchLib(std::size_t indexLib, const size_t indexGame) const;
            size_t manageDynamicSwitchGame(const std::size_t indexLib, size_t indexGame) const;
            void incrementGameTime(const std::chrono::steady_clock::time_point clockT2,
            std::chrono::steady_clock::time_point &clockT0, const std::size_t indexGame) const noexcept;
            void accelerateMovement(GameStatus &status, unsigned int &msTimer) const noexcept;
            std::vector<DLLoader<IDisplayModule> *> _libLoader;
            std::vector<DLLoader<IGameModule> *> _gameLoader;
            std::vector<arcade::IGameModule *> _game;
            std::vector<arcade::IDisplayModule *> _lib;
            std::vector<std::string> _gameText;
            std::vector<std::string> _libText;
            std::array<std::string, 3> _libName;
            std::array<std::string, 3> _gameName;
    };
}

#endif /* !CORE_HPP_ */
