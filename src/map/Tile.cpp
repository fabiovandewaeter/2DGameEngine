#include "map/Tile.hpp"

#include "systems/Camera.hpp"
#include "Texture.hpp"

Tile::Tile(Texture *texture, int x, int y)
{
    this->texture = texture;
    this->x = x;
    this->y = y;
}
Tile::~Tile() {}

void Tile::render(Camera *camera)
{
    SDL_Rect renderBox = (SDL_Rect){this->x, this->y, TILE_SIZE, TILE_SIZE};
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderBox);
    }
}

int Tile::getCenterX() { return TILE_SIZE / 2; }
int Tile::getCenterY() { return TILE_SIZE / 2; }
int Tile::getTextureId() { return this->texture->getId(); }
int Tile::getTileSize() { return TILE_SIZE; }