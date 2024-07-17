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

    void render(const Snake &snake, Apple const &apple);

    void updateWindowTitle(int score, int fps);

    SDL_Window *getSdlWindow();
    bool is_full_screen = false;

    [[maybe_unused]] [[nodiscard]] int getSdlWindowFlags() const;

private:
    SDL_Window *sdl_window{};
    SDL_Renderer *renderer{};
    ResourceManager &res_manager;
    int sdl_window_flags = 0;

    const int screen_width;
    const int screen_height;
    const unsigned int grid_width;
    const unsigned int grid_height;

    static void initSdl() ;

    void createWindow();

    void createRenderer();

    void cleanScreen() const;

    SDL_Rect &renderApple(const Apple &apple, SDL_Rect &loc_rect) const;

    SDL_Rect &renderSnakeBody(const Snake &snake, SDL_Rect &loc_rect) const;

    static SDL_Rect &renderSnakeHead(const Snake &snake, SDL_Rect &loc_rect) ;

    void updateScreen() const;
};

#endif
