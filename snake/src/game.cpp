#include <iostream>

#include "src/tools/logger/logger.hpp"
#include "output_file_logger/output_file_logger.hpp"
#include "game.hpp"

Game::Game(unsigned int grid_width, unsigned int grid_height)
        : snake(grid_width, grid_height),
          random_generator_engine(dev()),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1)) {
    placeFood();
}

void Game::placeFood() {
    int x, y;
    while (true) {
        x = random_w(random_generator_engine);
        y = random_h(random_generator_engine);
        if (!snake.thereIsASnakeInCell(x, y)) {
            apple.setPos(x, y);
            return;
        }
    }
}

void Game::updateState() {
    if (!snake.is_alive) return;

    snake.update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    handleSnakeHitFood(new_x, new_y);
}

void Game::handleSnakeHitFood(int new_x, int new_y) {
    if (apple.getPosX() == new_x && apple.getPosY() == new_y) {
        score += kXpApple;
        ++apples_fetched;
        placeFood();
        snake.growBody();
        snake.increaseSpeed();
    }
}

int Game::getScore() const { return score; }

int Game::getSnakeBodySize() const { return snake.body_size; }

int Game::getApplesFetched() const { return apples_fetched; }

void Game::updateWindowTitle(Renderer &renderer, Uint32 frame_end, Uint32 &title_timestamp, int &frame_count) const {
    renderer.updateWindowTitle(score, frame_count);
    frame_count = 0;
    title_timestamp = frame_end;
}

void Game::logGameStartToFile() {
    OutputFileLogger score_saver;
    score_saver.saveGameStart();
}

void Game::logGameEndToFile() const {
    log("Your score: %i\n", getScore());
    OutputFileLogger score_saver;
    score_saver.saveGameEnd(getScore(), getSnakeBodySize(),
                            getApplesFetched(), snake.speed);
}

void Game::run(EventController const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    logGameStartToFile();
    while (running) {
        frame_start = SDL_GetTicks();

        // Loop cycle actions
        controller.handleInput(running, snake, renderer.getSdlWindow(),
                               renderer.is_full_screen);
        updateState();
        renderer.render(snake, apple);
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop cycle takes
        ++frame_count;
        frame_duration = frame_end - frame_start;

        if (frame_end - title_timestamp >= kOneSecInMs)
            updateWindowTitle(renderer, frame_end, title_timestamp, frame_count);

        // Adjust the frame rate if the time for this frame is too small
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}
