#include "apple.hpp"

void Apple::SetPos(int x, int y) {
    pos_x = x;
    pos_y = y;
}

int Apple::GetPosX() const { return pos_x; }

int Apple::GetPosY() const { return pos_y; }
