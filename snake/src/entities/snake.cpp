#include <algorithm>
#include <cmath>

#include "snake.hpp"

void Snake::update() {
    SDL_Point prev_cell{
            static_cast<int>(head_x),
            static_cast<int>(head_y)
    };
    updateHead();
    SDL_Point current_cell{
            static_cast<int>(head_x),
            static_cast<int>(head_y)
    };

    if (hasSnakeHeadMoved(prev_cell, current_cell)) {
        updateBody(prev_cell);
    }

    if (areConditionsForSnakeToDie(current_cell))
        kill();
}

void Snake::kill() {
    is_alive = false;
}

bool Snake::hasSnakeHeadMoved(const SDL_Point &prev_cell, const SDL_Point &current_cell) {
    return current_cell.x != prev_cell.x || current_cell.y != prev_cell.y;
}

void Snake::changeDirection(Snake::Direction input, Snake::Direction opposite) {
    if (direction != opposite || body_size == 1)
        direction = input;
}

void Snake::increaseSpeed() {
    speed += kSnakeIncreaseSpeed;
    if (speed > kSnakeInitialSpeedMaxTotal)
        speed = kSnakeInitialSpeedMaxTotal;
}

void Snake::updateHead() {
    switch (direction) {
        case Direction::kLeft:
            head_x -= speed;
            break;

        case Direction::kRight:
            head_x += speed;
            break;

        case Direction::kUp:
            head_y -= speed;
            break;

        case Direction::kDown:
            head_y += speed;
            break;
    }
    wrapSnakeIfGoesOffScreen();
}

void Snake::wrapSnakeIfGoesOffScreen() {
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::updateBody(SDL_Point &prev_cell) {
    addPreviousHeadCellToSnakeBody(prev_cell);

    if (grow_body_size <= 0) {
        removeTailFromSnakeBody();
    } else {
        grow_body_size -= 1;
        ++body_size;
    }
}

bool Snake::areConditionsForSnakeToDie(const SDL_Point &current_head_cell) {
    if (is_dead_when_bite_own_tail)
        for (auto const &item: body_pieces) {
            if (current_head_cell.x == item.x && current_head_cell.y == item.y)
                return true;
        }
    return false;
}

void Snake::removeTailFromSnakeBody() {
    body_pieces.erase(body_pieces.begin());
    grow_body_size = 0;
}

void Snake::addPreviousHeadCellToSnakeBody(const SDL_Point &prev_head_cell) {
    body_pieces.push_back(prev_head_cell);
}

void Snake::growBody() {
    grow_body_size = app_options::snakeBodySizeToIncrease();
}

bool Snake::thereIsASnakeInCell(int x, int y) {
    if (isSnakeHeadInCell(x, y)) {
        return true;
    }

    return std::ranges::any_of(body_pieces, [x, y](const SDL_Point& item) {
        return x == item.x && y == item.y;
    });
}

bool Snake::isSnakeHeadInCell(int x, int y) const {
    return x == static_cast<int>(head_x) && y == static_cast<int>(head_y);
}
