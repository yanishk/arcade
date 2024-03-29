/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-yanis.harkouk
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>

template<typename T>
class DLLoader {
    public:
        DLLoader(std::string pathLib) {
            _handle = dlopen(pathLib.c_str(), RTLD_LAZY);
            if (!_handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(84);
            }
            dlerror();
        };
        ~DLLoader() = default;

        T *getInstance() {
            T *(*cosine)(void);
            cosine = (T*(*)(void)) dlsym(_handle, "entryPoint");
            char *error = dlerror();
            if (error != NULL) {
                fprintf(stderr, "%s\n", error);
                exit(84);
            }
            return (*cosine)();
        };

        void closeLib() {
            if (dlclose(_handle) != 0) {
                exit(84);
            }
        };

    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */
