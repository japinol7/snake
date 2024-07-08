#include <iostream>
#include <string>
#include <tuple>

#include <SDL_image.h>

#include "src/tools/utils/utils.hpp"
#include "src/arguments_parser/arguments_parser.hpp"
#include "renderer.hpp"

using std::get;

Renderer::Renderer(const int screen_width, const int screen_height,
                   const unsigned int grid_width, const unsigned int grid_height)
        : screen_width(screen_width), screen_height(screen_height),
          grid_width(grid_width), grid_height(grid_height) {
    InitSDL();
    CreateWindow();
    CreateRenderer();
    LoadTextures();
}

void Renderer::InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Renderer::CreateWindow() {
    int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS;
    if (app_options::IsFullScreen())
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    sdl_window = SDL_CreateWindow(
            kAppNameWithVersion.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screen_width, kWinHeight, window_flags);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Renderer::CreateRenderer() {
    int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    renderer = SDL_CreateRenderer(sdl_window, -1, renderer_flags);
    if (nullptr == renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::LoadTextures() {
    background_texture = LoadTexture(renderer, kFileNameImgBackground, screen_width, screen_height);
    score_zone_texture = LoadTexture(renderer, kFileNameImgScoreZone, score_zone_rect.w, score_zone_rect.h);
    jp_logo_texture = LoadTexture(renderer, kFileNameImgLogoJp, jp_logo_rect.w, jp_logo_rect.h);
}

void Renderer::CleanScreen() const {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, nullptr, nullptr);

    SDL_Rect rect_dest {0, kWinHeight - score_zone_rect.h,
                        score_zone_rect.w, score_zone_rect.h};
    SDL_RenderCopy(renderer, score_zone_texture, &score_zone_rect, &rect_dest);

    SDL_Rect logo_rect_dest {screen_width - jp_logo_rect.w, kWinHeight - jp_logo_rect.h,
                             jp_logo_rect.w, jp_logo_rect.h};
    SDL_RenderCopy(renderer, jp_logo_texture, &jp_logo_rect, &logo_rect_dest);
}

void Renderer::Render(Snake const &snake, Apple const &apple) {
    SDL_Rect loc_rect;
    loc_rect.w = screen_width / grid_width;
    loc_rect.h = screen_height / grid_height;

    CleanScreen();

    loc_rect = RenderApple(apple, loc_rect);
    loc_rect = RenderSnakeBody(snake, loc_rect);
    loc_rect = RenderSnakeHead(snake, loc_rect);

    if (snake.is_alive) {
        SDL_SetRenderDrawColor(renderer, 0, 83, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &loc_rect);

    UpdateScreen();
}

void Renderer::UpdateScreen() const {
    SDL_RenderPresent(renderer);
}

SDL_Rect &Renderer::RenderSnakeHead(const Snake &snake, SDL_Rect &loc_rect) {
    loc_rect.x = static_cast<int>(snake.head_x) * loc_rect.w;
    loc_rect.y = static_cast<int>(snake.head_y) * loc_rect.h;
    return loc_rect;
}

SDL_Rect &Renderer::RenderSnakeBody(const Snake &snake, SDL_Rect &loc_rect) const {
    SDL_SetRenderDrawColor(renderer, 100, 0, 255, 255);
    for (SDL_Point const &point: snake.body_pieces) {
        loc_rect.x = point.x * loc_rect.w;
        loc_rect.y = point.y * loc_rect.h;
        SDL_RenderFillRect(renderer, &loc_rect);
    }
    return loc_rect;
}

SDL_Rect &Renderer::RenderApple(const Apple &apple, SDL_Rect &loc_rect) const {
    SDL_SetRenderDrawColor(renderer, 150, 220, 0, 255);
    loc_rect.x = apple.GetPosX() * loc_rect.w;
    loc_rect.y = apple.GetPosY() * loc_rect.h;
    SDL_RenderFillRect(renderer, &loc_rect);
    return loc_rect;
}

void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{kAppNameWithVersion + " - Score: " + std::to_string(score)
                      + " - FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}