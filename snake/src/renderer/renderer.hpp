#ifndef JP_RENDERER_HPP
#define JP_RENDERER_HPP

#include "SDL.h"

#include "src/entities/apple.hpp"
#include "src/entities/snake.hpp"

class Renderer {
public:
    Renderer(int screen_width, int screen_height,
             unsigned int grid_width, unsigned int grid_height);

    ~Renderer();

    void Render(const Snake& snake, Apple const &apple);

    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *sdl_window{};
    SDL_Renderer *renderer{};

    SDL_Texture *background_texture = nullptr;
    SDL_Texture *score_zone_texture = nullptr;
    SDL_Rect score_zone_rect = {0, 0, 1080, 47};
    SDL_Rect jp_logo_rect = {0, 0, 208, 47};
    SDL_Texture *jp_logo_texture = nullptr;

    const int screen_width;
    const int screen_height;
    const unsigned int grid_width;
    const unsigned int grid_height;

    static void InitSDL() ;

    void CreateWindow();

    void CreateRenderer();

    void CleanScreen() const;

    void LoadTextures();

    SDL_Rect &RenderApple(const Apple &apple, SDL_Rect &loc_rect) const;

    SDL_Rect &RenderSnakeBody(const Snake &snake, SDL_Rect &loc_rect) const;

    static SDL_Rect &RenderSnakeHead(const Snake &snake, SDL_Rect &loc_rect) ;

    void UpdateScreen() const;
};

#endif
