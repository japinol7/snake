#ifndef JP_UTILS_HPP
#define JP_UTILS_HPP

#include "SDL.h"

#include <charconv>
#include <string_view>

template<typename T>
bool StringViewToNum(const std::string_view &view, T &value) {
    if (view.empty()) {
        return false;
    }

    const char *first = view.data();
    const char *last = view.data() + view.length();
    std::from_chars_result res = std::from_chars(first, last, value);

    if (res.ec != std::errc()) {
        return false;
    }
    if (res.ptr != last) {
        return false;
    }
    return true;
}


SDL_Texture *LoadTexture(
        SDL_Renderer *renderer, const char *image_path,
        int width, int height);

#endif
