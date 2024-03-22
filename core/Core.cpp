/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <iostream>
#include "Core.hpp"

arcade::Core::Core(std::string libPath) : _exit(false)
{
    std::string gamePath = "lib/nibbler.so";
    _lib.push_back(openLib(libPath));
    _game.push_back(openGame(gamePath));
}

std::pair<arcade::IGameModule *, void *> arcade::Core::openGame(std::string path)
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
    return std::make_pair((*cosine)(), handle);
}

std::pair<arcade::IDisplayModule *, void *> arcade::Core::openLib(std::string path)
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
    return std::make_pair((*cosine)(), handle);
}

void arcade::Core::initLoop()
{
    _lib[0].first->init(_game[0].first->getPattern());
    _game[0].first->stockPlayerPos();
    while (!_exit) {
        _lib[0].first->displayText(_game[0].first->getText());
        _exit = _lib[0].first->game(_game[0].first->getMap());
        _game[0].first->updateMap(_lib[0].first->getKey());
        _lib[0].first->setKey(OTHER);
    }
    _lib[0].first->stop();
    dlclose(_lib[0].second);
}

void arcade::Core::setExit(bool exit)
{
    _exit = exit;
}
