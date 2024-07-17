#ifndef JP_SNAKE_HPP
#define JP_SNAKE_HPP

#include <vector>

#include "SDL.h"

#include "src/config/constants.hpp"
#include "src/arguments_parser/arguments_parser.hpp"

class Snake {
public:
    enum class Direction {
        kUp,
        kDown,
        kLeft,
        kRight,
    };

    Snake(unsigned int grid_width, unsigned int grid_height)
            : grid_width(grid_width),
              grid_height(grid_height),
              head_x(grid_width / 2),
              head_y(grid_height / 2) {}

    void update();

    void growBody();

    bool thereIsASnakeInCell(int x, int y);

    void changeDirection(Snake::Direction input, Snake::Direction opposite);

    void increaseSpeed();

    float head_x;
    float head_y;
    std::vector<SDL_Point> body_pieces;
    Direction direction = Direction::kUp;
    bool is_dead_when_bite_own_tail = kSnakeDieWhenBiteOwnTail;
    int body_size{0};
    bool is_alive{true};
    float speed{app_options::snakeInitialSpeed()};

private:
    void updateHead();

    void updateBody(SDL_Point &prev_cell);

    int grow_body_size{app_options::snakeInitialBodySize()};
    unsigned int grid_width;
    unsigned int grid_height;

    [[nodiscard]] bool isSnakeHeadInCell(int x, int y) const;

    void addPreviousHeadCellToSnakeBody(const SDL_Point &prev_head_cell);

    void removeTailFromSnakeBody();

    bool areConditionsForSnakeToDie(const SDL_Point &current_head_cell);

    void kill();

    static bool hasSnakeHeadMoved(const SDL_Point &prev_cell, const SDL_Point &current_cell) ;

    void wrapSnakeIfGoesOffScreen();
};

#endif
