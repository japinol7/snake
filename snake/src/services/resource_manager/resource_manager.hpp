#ifndef JP_RESOURCE_MANAGER_HPP
#define JP_RESOURCE_MANAGER_HPP

#include <iostream>
#include <map>

#include "SDL.h"

#include "src/config/constants.hpp"

class ResourceManager {
public:
    ResourceManager();

    ~ResourceManager();

    void LoadTextures(SDL_Renderer *renderer, int screen_width, int screen_height);

    std::map<std::string, SDL_Texture *> textures;

    [[nodiscard]] const SDL_Rect &GetScoreZoneRect() const {
        return score_zone_rect;
    }

    [[nodiscard]] const SDL_Rect &GetJpLogoRect() const {
        return jp_logo_rect;
    }

private:
    SDL_Rect score_zone_rect = {0, 0, 1080, 47};
    SDL_Rect jp_logo_rect = {0, 0, 208, 47};
};

#endif
