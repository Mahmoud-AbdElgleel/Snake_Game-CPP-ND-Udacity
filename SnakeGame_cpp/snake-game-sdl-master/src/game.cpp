#include "game.h"

#include <iostream>
#ifdef __WIN32__
#include "SDL.h"
#elif __linux__
#include <SDL2/SDL.h>
#endif

Game::Game(std::size_t width_grid, std::size_t grid_height, std::string map_path)
    : snake(width_grid, grid_height), map(map_path), engine(dev()), random_w(0, static_cast<int>(width_grid - 1)), random_h(0, static_cast<int>(grid_height - 1)) {
    map.LoadMap();
    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_durationOf_Frame) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 endOf_Frame;
    Uint32 durationOf_Frame;
    int frame_count = 0;
    
    
    bool IsRunning = true;

    while  (IsRunning) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(IsRunning, snake);
        Update();
        renderer.Render(map, snake, food);

        endOf_Frame = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        durationOf_Frame = endOf_Frame - frame_start;

        // After every second, update the window title.
        if (endOf_Frame - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = endOf_Frame;
        }

        // If the time for this frame is too small (i.e. durationOf_Frame is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (durationOf_Frame < target_durationOf_Frame) {
            SDL_Delay(target_durationOf_Frame - durationOf_Frame);
        }
    }
}

void Game::PlaceFood() {
    int p, place_y;
    while (true) {
        place_x = random_w(engine);
        place_y = random_h(engine);
        // make sure  that the location is empty before placing
        // food.
        if (!snake.SnakeCell(place_x, place_y) && !map.MapCell(place_x, place_y)) {
            food.x = place_x;
            food.y = place_y;
            return;
        }
    }
}

void Game::Update() {
    if (!snake.alive) return;

    snake.Update(std::move((map.getMap())));

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody();
        snake.speed += 0.02;
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }