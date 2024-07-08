#ifndef JP_CONTROLLER_HPP
#define JP_CONTROLLER_HPP

#include "src/entities/snake.hpp"

class EventController {
public:
    static void HandleInput(bool &running, Snake &snake);

private:
    static void HandleKeyDown(bool &running, Snake &snake, const SDL_Event &e);
};

#endif
