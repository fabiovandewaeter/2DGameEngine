#include "Map.hpp"

Map::Map() {}
Map::~Map()
{
    for (Tile *tile : this->tiles)
    {
        delete tile;
    }
    tiles.clear();
}

void Map::init(int tileWidth, int tileHeight)
{
    this->tileWidth;
    this->tileHeight;
}

void Map::render(SDL_Renderer *renderer, Camera *camera)
{
    for (Tile *tile : this->tiles)
    {
        tile->render(renderer, camera);            
    }
}