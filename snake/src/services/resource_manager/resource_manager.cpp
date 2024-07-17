#include "src/tools/utils/utils.hpp"
#include "resource_manager.hpp"

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

void ResourceManager::loadTextures(
        SDL_Renderer *renderer, int screen_width, int screen_height) {
    textures["background"] = loadTexture(renderer, kFileNameImgBackground,
                                         screen_width, screen_height);
    textures["score_zone"] = loadTexture(renderer, kFileNameImgScoreZone, score_zone_rect.w, score_zone_rect.h);
    textures["jp_logo"] = loadTexture(renderer, kFileNameImgLogoJp, jp_logo_rect.w, jp_logo_rect.h);
}
