#ifndef JP_APPLE_HPP
#define JP_APPLE_HPP

#include "SDL.h"

#include "src/entities/snake.hpp"

class Apple {
public:
    void setPos(int x, int y);

    [[nodiscard]] int getPosX() const;

    [[nodiscard]] int getPosY() const;

    void draw(SDL_Renderer *renderer, SDL_Rect &loc_rect) const;

    std::vector<Uint8> color{150, 220, 0};

private:
    int pos_x{0};
    int pos_y{0};
};

#endif
