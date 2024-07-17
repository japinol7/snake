#include "apple.hpp"

void Apple::setPos(int x, int y) {
    pos_x = x;
    pos_y = y;
}

int Apple::getPosX() const { return pos_x; }

int Apple::getPosY() const { return pos_y; }
