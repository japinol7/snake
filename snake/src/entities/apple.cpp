#include "apple.hpp"

void Apple::setPos(int x, int y) {
    pos_x = x;
    pos_y = y;
}

int Apple::getPosX() const { return pos_x; }

int Apple::getPosY() const { return pos_y; }

void Apple::draw(SDL_Renderer *renderer, SDL_Rect &loc_rect) const {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    loc_rect.x = getPosX() * loc_rect.w;
    loc_rect.y = getPosY() * loc_rect.h;
    SDL_RenderFillRect(renderer, &loc_rect);
}
