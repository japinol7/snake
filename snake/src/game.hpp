#ifndef JP_GAME_HPP
#define JP_GAME_HPP

#include <random>

#include "SDL.h"

#include "src/controller/controller.hpp"
#include "src/renderer/renderer.hpp"
#include "src/entities/apple.hpp"
#include "src/entities/snake.hpp"

class Game {
public:
    Game(unsigned int grid_width, unsigned int grid_height);

    void run(EventController const &controller, Renderer &renderer,
             std::size_t target_frame_duration);

    [[nodiscard]] int getScore() const;

    [[nodiscard]] int getSnakeBodySize() const;

    [[nodiscard]] int getApplesFetched() const;

    static void logGameStartToFile() ;

    void logGameEndToFile() const;

private:
    Apple apple;
    Snake snake;

    std::random_device dev;
    std::mt19937 random_generator_engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int score{0};
    int apples_fetched{0};

    void placeFood();

    void updateState();

    void handleSnakeHitFood(int new_x, int new_y);

    void updateWindowTitle(Renderer &renderer, Uint32 frame_end, Uint32 &title_timestamp,
                           int &frame_count) const;
};

#endif
