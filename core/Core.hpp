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
            void updateGame(GameStatus &status, unsigned int &msTimer, const std::size_t indexGame, const std::size_t score) const noexcept;
            std::vector<std::pair<std::string, std::pair<int, int>>> getGameScores(std::string gameName) const noexcept;
            void updateScoreFile(std::string gameName, std::size_t score) const noexcept;
            arcade::GameStatus handleMenuKey(GameStatus status) noexcept;
            void choseOptionMenu() noexcept;
            arcade::GameStatus mainGame(GameStatus status) noexcept;
            void endLoop() const noexcept;
            void createObjectLoader(const std::string libPath) noexcept;
            std::vector<DLLoader<IDisplayModule> *> _libLoader;
            std::vector<DLLoader<IGameModule> *> _gameLoader;
            std::vector<arcade::IGameModule *> _game;
            std::vector<arcade::IDisplayModule *> _lib;
            std::vector<std::string> _gameText;
            std::vector<std::string> _libText;
            std::array<std::string, 3> _libName;
            std::array<std::string, 3> _gameName;
            std::size_t _indexLib = 0;
            std::size_t _indexGame = 0;
            std::size_t _tmpLib = 0;
            std::size_t _tmpGame = 0;
            std::size_t _score = 0;
    };
}

#endif /* !CORE_HPP_ */
