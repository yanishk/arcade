/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <iostream>
#include "Core.hpp"
#include "DLLoader.hpp"

arcade::Core::Core(std::string libPath) : _exit(false)
{
    std::string gamePath = "lib/nibbler.so";
    _lib.push_back(openLib(libPath));
    _game.push_back(openGame(gamePath));
}

arcade::IGameModule *arcade::Core::openGame(std::string path)
{
    arcade::IGameModule *(*cosine)(void);
    char *error;
    void *handle;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    cosine = (arcade::IGameModule *(*)(void)) dlsym(handle, "entryPoint");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(84);
    }
    return (*cosine)();
}

arcade::IDisplayModule *arcade::Core::openLib(std::string path)
{
    arcade::IDisplayModule *(*cosine)(void);
    char *error;
    void *handle;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    cosine = (arcade::IDisplayModule *(*)(void)) dlsym(handle, "entryPoint");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(84);
    }
    return (*cosine)();
}

void arcade::Core::initLoop()
{
    _lib[0]->init(_game[0]->getPattern());
    _game[0]->stockPlayerPos();
    while (!_exit) {
        _lib[0]->displayText(_game[0]->getText());
        _exit = _lib[0]->game(_game[0]->getMap());
        _game[0]->updateMap(_lib[0]->getKey());
        _lib[0]->setKey(arcade::KeyPressed::OTHER);
    }
    _lib[0]->stop();
    dlclose(_lib[0]);
}

void arcade::Core::setExit(bool exit)
{
    _exit = exit;
}
