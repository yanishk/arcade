/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <dlfcn.h>
#include <iostream>

arcade::Core::Core() : _exit(false)
{
}

arcade::Core::~Core()
{
}

void arcade::Core::openLib(std::string path)
{
    void *handle;
    arcade::IDisplayModule *(*cosine)(void);
    char *error;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return;
    }
    dlerror();
    cosine = (arcade::IDisplayModule *(*)(void)) dlsym(handle, "entryPoint");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        return;
    }
    arcade::IDisplayModule *_lib = (*cosine)();
    _lib->init();
    initLoop(_lib);
    _lib->stop();
    dlclose(handle);
    return;
}

void arcade::Core::initLoop(auto _lib)
{
    while (!_exit) {
        _exit = _lib->game();
    }
}

void arcade::Core::setExit(bool exit)
{
    _exit = exit;
}