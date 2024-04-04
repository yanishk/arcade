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
#include <memory>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"

namespace arcade
{
    class Core
    {
        public:
            Core(std::string libPath);
            ~Core() = default;

            void loop();

        private:
            void endLoop() const noexcept;
            void readLib(const std::string libPath);
            void manageMenuSwitchLib(const std::size_t indexLib, const std::size_t indexGame, const std::size_t tmp) const;
            void manageMenuSwitchGame(const std::size_t indexLib, const std::size_t indexGame, const std::size_t tmp) const;
            std::size_t manageDynamicSwitchLib(std::size_t indexLib, const std::size_t indexGame) const;
            std::size_t manageDynamicSwitchGame(const std::size_t indexLib, std::size_t indexGame);
            void incrementGameTime(const std::chrono::steady_clock::time_point clockT2,
            std::chrono::steady_clock::time_point &clockT0, const std::size_t indexGame) const noexcept;
            void updateGame(GameStatus &status, unsigned int &msTimer, const std::size_t indexGame, const std::size_t score) noexcept;
            std::vector<std::pair<std::string, std::pair<int, int>>> getGameScores(const std::string gameName) const noexcept;
            void updateScoreFile(const std::string gameName, const std::size_t score) noexcept;
            arcade::GameStatus handleMenuKey(GameStatus status);
            void choseOptionMenu();
            arcade::GameStatus mainGame(GameStatus status);
            void createObjectLoader(const std::string libPath);
            std::vector<std::unique_ptr<DLLoader<IDisplayModule>>> _libLoader;
            std::vector<std::unique_ptr<DLLoader<IGameModule>>> _gameLoader;
            std::vector<std::unique_ptr<arcade::IGameModule>> _game;
            std::vector<std::unique_ptr<arcade::IDisplayModule>> _lib;
            std::vector<std::string> _gameText;
            std::vector<std::string> _libText;
            std::array<std::string, 13> _libName;
            std::array<std::string, 7> _gameName;
            std::string _playerName;
            std::size_t _indexLib;
            std::size_t _indexGame;
            std::size_t _tmpLib;
            std::size_t _tmpGame;
            std::size_t _score;
    };
}

#endif /* !CORE_HPP_ */
