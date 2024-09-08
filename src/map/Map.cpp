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

void Map::render(SDL_Renderer *renderer, int cameraCenterX, int cameraCenterY, int cameraCoordinateX, int cameraCoordinateY, double scale, Camera *camera)
{
    for (Tile *tile : this->tiles)
    {
        tile->render(renderer, cameraCenterX, cameraCenterY, cameraCoordinateX, cameraCoordinateY, scale, camera);
    }
}