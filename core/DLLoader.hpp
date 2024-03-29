/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include "Error.hpp"

template<typename T>
class DLLoader {
    public:
        DLLoader(const std::string pathLib) {
            _handle = dlopen(pathLib.c_str(), RTLD_LAZY);
            if (!_handle)
                throw arcade::Error(dlerror());
        };
        ~DLLoader() = default;

        T *getInstance() {
            T *(*cosine)(void);
            cosine = (T*(*)(void)) dlsym(_handle, "entryPoint");
            char *errorMessage = dlerror();
            if (errorMessage != NULL)
                throw arcade::Error(errorMessage);
            return (*cosine)();
        };

        void closeLib() {
            if (dlclose(_handle) != 0)
                throw arcade::Error(dlerror());
        };

    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */
