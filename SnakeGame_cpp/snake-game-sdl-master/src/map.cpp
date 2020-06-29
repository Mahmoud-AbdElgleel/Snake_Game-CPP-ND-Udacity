#include "map.h"

#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {}

// Load map from text file
void Map::LoadMap() {
    std::string line, cell_count;
    SDL_Point point;
    std::ifstream map{_filepath};
    if (map.is_open()) {
        for (size_t count_ = 0; count_ < 32; count_++) {
            getline(map, line);
            std::istringstream linestream(line);
            for (size_t jj = 0; jj < 32; jj++) {
                linestream >> cell_count;
                if (std::stoi(cell_count) == 1) {
                    point.x = jj;
                    point.y = count_;
                    _map.push_back(point);
                }
            }
        }
    }
    map.close();
}

// Render the map on screen on call

void Map::RenderMap(SDL_Renderer* sdl_renderer, SDL_Rect* block) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x66, 0x66, 0x66, 0x01);
    for (auto const& points : _map) {
        block->x = points.x * block->w;
        block->y = points.y * block->h;
        SDL_RenderFillRect(sdl_renderer, block);
    }
}

// Check if given point is in map or not

bool Map::MapCell(int x, int y) {
    for (auto const& points : _map) {
        if (points.x == x && points.y == y)
            return true;
    }
    return false;
}
