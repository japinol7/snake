#ifndef JP_RENDERER_HPP
#define JP_RENDERER_HPP

#include "SDL.h"

#include "src/services/resource_manager/resource_manager.hpp"
#include "src/entities/apple.hpp"
#include "src/entities/snake.hpp"

class Renderer {
public:
    Renderer(int screen_width, int screen_height,
             unsigned int grid_width, unsigned int grid_height,
             const ResourceManager& resource_manager);

    ~Renderer();

    void Render(const Snake& snake, Apple const &apple);

    void UpdateWindowTitle(int score, int fps);

    SDL_Window *GetSdlWindow();
    bool is_full_screen = false;

    [[maybe_unused]] [[nodiscard]] int GetSdlWindowFlags() const;

private:
    SDL_Window *sdl_window{};
    SDL_Renderer *renderer{};
    ResourceManager &res_manager;
    int sdl_window_flags = 0;

    const int screen_width;
    const int screen_height;
    const unsigned int grid_width;
    const unsigned int grid_height;

    static void InitSDL() ;

    void CreateWindow();

    void CreateRenderer();

    void CleanScreen() const;

    SDL_Rect &RenderApple(const Apple &apple, SDL_Rect &loc_rect) const;

    SDL_Rect &RenderSnakeBody(const Snake &snake, SDL_Rect &loc_rect) const;

    static SDL_Rect &RenderSnakeHead(const Snake &snake, SDL_Rect &loc_rect) ;

    void UpdateScreen() const;
};

#endif
