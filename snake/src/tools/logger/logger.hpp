#ifndef JP_LOGGER_HPP
#define JP_LOGGER_HPP

#include <SDL_log.h>

template<typename... T>
void Log(const char *fmt, T... args) {
    SDL_Log(fmt, args...);
}

#endif
