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

void Map::init(Texture *tileTextures)
{
    this->tileSize = 16;
    this->tileTextures = tileTextures;
    loadTiles();
}

void Map::loadTiles()
{
    this->tiles.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, 0, this->tileSize, this->tileSize}));
}

void Map::render(SDL_Renderer *renderer, Camera *camera)
{
    printf("un\n");
    for (Tile *tile : this->tiles)
    {
        printf("deux\n");
        tile->render(renderer, camera);
    }
}