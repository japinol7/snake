#include <iostream>
#include <string>
#include <tuple>

#include <SDL_image.h>

#include "src/arguments_parser/arguments_parser.hpp"
#include "renderer.hpp"

using std::get;

Renderer::Renderer(const int screen_width, const int screen_height,
                   const unsigned int grid_width, const unsigned int grid_height,
                   const ResourceManager& resource_manager)
        : screen_width(screen_width), screen_height(screen_height),
          grid_width(grid_width), grid_height(grid_height),
          res_manager(const_cast<ResourceManager &>(resource_manager)) {
    initSdl();
    createWindow();
    createRenderer();
    res_manager.loadTextures(renderer, screen_width, screen_height);
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::initSdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Renderer::createWindow() {
    sdl_window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS;
    is_full_screen = app_options::isFullScreen();
    if (is_full_screen)
        sdl_window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    sdl_window = SDL_CreateWindow(
            kAppNameWithVersion.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screen_width, kWinHeight, sdl_window_flags);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Renderer::createRenderer() {
    int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    renderer = SDL_CreateRenderer(sdl_window, -1, renderer_flags);
    if (nullptr == renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Renderer::cleanScreen() const {
    SDL_Rect jp_logo_rect = res_manager.getJpLogoRect();
    SDL_Rect score_zone_rect = res_manager.getScoreZoneRect();

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, res_manager.textures["background"], nullptr, nullptr);

    SDL_Rect rect_dest {0, kWinHeight - score_zone_rect.h,
                        score_zone_rect.w, score_zone_rect.h};
    SDL_RenderCopy(renderer, res_manager.textures["score_zone"], nullptr, &rect_dest);

    SDL_Rect logo_rect_dest {screen_width - jp_logo_rect.w, kWinHeight - jp_logo_rect.h,
                             jp_logo_rect.w, jp_logo_rect.h};
    SDL_RenderCopy(renderer, res_manager.textures["jp_logo"], nullptr, &logo_rect_dest);
}

void Renderer::render(const Snake &snake, Apple const &apple) {
    SDL_Rect loc_rect;
    loc_rect.w = screen_width / grid_width;
    loc_rect.h = screen_height / grid_height;

    cleanScreen();

    loc_rect = renderApple(apple, loc_rect);
    loc_rect = renderSnakeBody(snake, loc_rect);
    loc_rect = renderSnakeHead(snake, loc_rect);

    if (snake.is_alive) {
        SDL_SetRenderDrawColor(renderer, 0, 83, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &loc_rect);

    updateScreen();
}

void Renderer::updateScreen() const {
    SDL_RenderPresent(renderer);
}

SDL_Rect &Renderer::renderSnakeHead(const Snake &snake, SDL_Rect &loc_rect) {
    loc_rect.x = static_cast<int>(snake.head_x) * loc_rect.w;
    loc_rect.y = static_cast<int>(snake.head_y) * loc_rect.h;
    return loc_rect;
}

SDL_Rect &Renderer::renderSnakeBody(const Snake &snake, SDL_Rect &loc_rect) const {
    SDL_SetRenderDrawColor(renderer, 100, 0, 255, 255);
    for (SDL_Point const &point: snake.body_pieces) {
        loc_rect.x = point.x * loc_rect.w;
        loc_rect.y = point.y * loc_rect.h;
        SDL_RenderFillRect(renderer, &loc_rect);
    }
    return loc_rect;
}

SDL_Rect &Renderer::renderApple(const Apple &apple, SDL_Rect &loc_rect) const {
    SDL_SetRenderDrawColor(renderer, 150, 220, 0, 255);
    loc_rect.x = apple.getPosX() * loc_rect.w;
    loc_rect.y = apple.getPosY() * loc_rect.h;
    SDL_RenderFillRect(renderer, &loc_rect);
    return loc_rect;
}

void Renderer::updateWindowTitle(int score, int fps) {
    std::string title{kAppNameWithVersion + " - Score: " + std::to_string(score)
                      + " - FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

SDL_Window *Renderer::getSdlWindow() {
    return sdl_window;
}

[[maybe_unused]] int Renderer::getSdlWindowFlags() const {
    return sdl_window_flags;
}
