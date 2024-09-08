#ifndef map_hpp
#define map_hpp

#include <vector>
#include "Tile.hpp"
#include "../systems/Camera.hpp"

class Map
{
public:
    Map();
    ~Map();

    void init(int tileWidth, int tileHeight);
    void render(SDL_Renderer *renderer, Camera *camera);
private:
    std::vector<Tile *> tiles;
    int tileWidth, tileHeight;
};

#endif