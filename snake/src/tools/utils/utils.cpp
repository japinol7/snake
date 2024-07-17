#include <SDL_image.h>

#include "utils.hpp"
#include "src/renderer/renderer.hpp"

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *image_path,
                         int width, int height) {
    SDL_Surface *bmpSurf = IMG_Load(image_path);

    if (bmpSurf == nullptr) {
        std::cerr << "Error. Cannot load image:" << image_path << "\n";
    }

    SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
    SDL_FreeSurface(bmpSurf);

    // Make a target texture to render to
    SDL_Texture *texTarget = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            width, height);
    // Render to the texture
    SDL_SetRenderTarget(renderer, texTarget);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bmpTex, nullptr, nullptr);
    // Detach the texture
    SDL_SetRenderTarget(renderer, nullptr);

    // Render the texture target to the screen
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texTarget, nullptr, nullptr);
    return texTarget;
}
