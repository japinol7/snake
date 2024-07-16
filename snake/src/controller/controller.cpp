#include "SDL.h"

#include "src/entities/snake.hpp"
#include "controller.hpp"

void EventController::HandleInput(bool &running, Snake &snake, SDL_Window *sdl_window,
                                  bool &is_full_screen) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
            continue;
        }

        if (e.type == SDL_KEYDOWN) {
            HandleKeyDown(running, snake, sdl_window, is_full_screen, e);
        }
    }
}

void EventController::HandleKeyDown(bool &running, Snake &snake, SDL_Window *sdl_window,
                                    bool &is_full_screen, const SDL_Event &e) {
    switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
            running = false;
            break;

        case SDLK_RETURN:
            if ((SDL_GetModState() & KMOD_ALT) == 0)
                break;

            is_full_screen = !is_full_screen;
            if (is_full_screen)
                SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            else
                SDL_SetWindowFullscreen(sdl_window, 0);
            break;

        case SDLK_UP:
        case SDLK_w:
            snake.ChangeDirection(Snake::Direction::kUp,
                                  Snake::Direction::kDown);
            break;

        case SDLK_DOWN:
        case SDLK_s:
            snake.ChangeDirection(Snake::Direction::kDown,
                                  Snake::Direction::kUp);
            break;

        case SDLK_LEFT:
        case SDLK_a:
            snake.ChangeDirection(Snake::Direction::kLeft,
                                  Snake::Direction::kRight);
            break;

        case SDLK_RIGHT:
        case SDLK_d:
            snake.ChangeDirection(Snake::Direction::kRight,
                                  Snake::Direction::kLeft);
            break;
    }
}
