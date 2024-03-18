/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>

namespace arcade
{
    class IDisplayModule
    {
        public:
            IDisplayModule() {};
            virtual ~IDisplayModule() {};

            virtual void init() = 0;
            virtual void stop() = 0;
            virtual const std::string &getName() const = 0;
            virtual void textDisplay(const std::string displayText,
                int xPos, int yPos) = 0;
            virtual bool game() = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */
