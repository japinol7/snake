#ifndef JP_CONTROLLER_HPP
#define JP_CONTROLLER_HPP

#include "src/entities/snake.hpp"

class EventController {
public:
    void handleInput(bool &running, Snake &snake, SDL_Window *sdl_window,
                     bool &is_full_screen) const;

private:
    static void handleKeyDown(bool &running, Snake &snake, SDL_Window *sdl_window,
                              bool &is_full_screen, const SDL_Event &e);
};

#endif
