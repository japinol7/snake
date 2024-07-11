#include "src/tools/utils/utils.hpp"
#include "resource_manager.hpp"

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

void ResourceManager::LoadTextures(
        SDL_Renderer *renderer, const int screen_width, const int screen_height) {
    textures["background"] = LoadTexture(renderer, kFileNameImgBackground,
                                         screen_width, screen_height);
    textures["score_zone"] = LoadTexture(renderer, kFileNameImgScoreZone, score_zone_rect.w, score_zone_rect.h);
    textures["jp_logo"] = LoadTexture(renderer, kFileNameImgLogoJp, jp_logo_rect.w, jp_logo_rect.h);
}
