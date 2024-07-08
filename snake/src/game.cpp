#include <iostream>

#include "src/tools/logger/logger.hpp"
#include "output_file_logger/output_file_logger.hpp"
#include "game.hpp"

Game::Game(unsigned int grid_width, unsigned int grid_height)
        : snake(grid_width, grid_height),
          random_generator_engine(dev()),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1)) {
    PlaceFood();
}

void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(random_generator_engine);
        y = random_h(random_generator_engine);
        if (!snake.ThereIsASnakeInCell(x, y)) {
            apple.SetPos(x, y);
            return;
        }
    }
}

void Game::UpdateState() {
    if (!snake.is_alive) return;

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    HandleSnakeHitFood(new_x, new_y);
}

void Game::HandleSnakeHitFood(int new_x, int new_y) {
    if (apple.GetPosX() == new_x && apple.GetPosY() == new_y) {
        score += kXpApple;
        ++apples_fetched;
        PlaceFood();
        snake.GrowBody();
        snake.IncreaseSpeed();
    }
}

int Game::GetScore() const { return score; }

int Game::GetSnakeBodySize() const { return snake.body_size; }

int Game::GetApplesFetched() const { return apples_fetched; }

void Game::UpdateWindowTitle(Renderer &renderer, Uint32 frame_end, Uint32 &title_timestamp, int &frame_count) const {
    renderer.UpdateWindowTitle(score, frame_count);
    frame_count = 0;
    title_timestamp = frame_end;
}

void Game::LogGameStartToFile() {
    OutputFileLogger score_saver;
    score_saver.SaveGameStart();
}

void Game::LogGameEndToFile() const {
    Log("Your score: %i\n", GetScore());
    OutputFileLogger score_saver;
    score_saver.SaveGameEnd(GetScore(), GetSnakeBodySize(),
                            GetApplesFetched(), snake.speed);
}

void Game::Run(EventController const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    LogGameStartToFile();
    while (running) {
        frame_start = SDL_GetTicks();

        // Loop cycle actions
        EventController::HandleInput(running, snake);
        UpdateState();
        renderer.Render(snake, apple);
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop cycle takes
        ++frame_count;
        frame_duration = frame_end - frame_start;

        if (frame_end - title_timestamp >= kOneSecInMs)
            UpdateWindowTitle(renderer, frame_end, title_timestamp, frame_count);

        // Adjust the frame rate if the time for this frame is too small
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}
