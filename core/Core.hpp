/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../lib/IDisplayModule.hpp"
#include <string>

namespace arcade {
    class Core {
        public:
            Core();
            ~Core();

            void initLoop(auto _lib);
            void setExit(bool exit);
            void openLib(std::string path);

        protected:
        private:
            bool _exit;
    };
}

#endif /* !CORE_HPP_ */
