#ifndef JP_APPLE_HPP
#define JP_APPLE_HPP

#include "SDL.h"

#include "src/entities/snake.hpp"

class Apple {
public:
    void setPos(int x, int y);

    [[nodiscard]] int getPosX() const;

    [[nodiscard]] int getPosY() const;

private:
    int pos_x{0};
    int pos_y{0};
};

#endif
