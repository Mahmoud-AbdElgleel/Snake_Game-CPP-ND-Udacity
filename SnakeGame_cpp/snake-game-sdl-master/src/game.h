#ifndef GAME_H
#define GAME_H

#include <random>

#include "controller.h"
#include "map.h"
#include "myrender.h"
#include "snake.h"

#ifdef __WIN32__
#include "SDL.h"
#elif __linux__
#include <SDL2/SDL.h>
#endif

class Game {
   public:
    Game(std::size_t grid_width, std::size_t grid_height, std::string map_path);
    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;

   private:
    Snake snake;
    SDL_Point food;
    Map map;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int score{0};

    void PlaceFood();
    void Update();
};

#endif