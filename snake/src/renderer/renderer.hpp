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

    void render(Snake &snake, Apple &apple);

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
    SDL_Rect screen_rect = {0, 0, screen_width, screen_height};
    const unsigned int grid_width;
    const unsigned int grid_height;


    static void initSdl() ;

    void createWindow();

    void createRenderer();

    void cleanScreen() const;

    void updateScreen() const;
};

#endif
