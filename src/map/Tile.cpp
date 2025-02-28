#include "map/Tile.hpp"

#include "systems/core/Camera.hpp"
#include "systems/game_objects/ItemFactory.hpp"
#include "Texture.hpp"

Item *Tile::defaultMineableResource = ItemFactory::getItem("Stone");

Tile::Tile(Texture *texture, float x, float y)
{
    this->texture = texture;
    this->x = x;
    this->y = y;
    this->mineableResource = Tile::defaultMineableResource;
}
Tile::Tile(Texture *texture, float x, float y, Item *mineableResource)
{
    this->texture = texture;
    this->x = x;
    this->y = y;
    this->mineableResource = mineableResource;
}
Tile::~Tile() {}

void Tile::render(Camera *camera)
{
    SDL_FRect renderBox = {this->x, this->y, 1, 1};
    SDL_Rect newRenderBox = camera->convertInGameToCameraCoordinates(renderBox);
    camera->render(this->texture, newRenderBox);
}

float Tile::getCenterX() { return TILE_SIZE / 2; }
float Tile::getCenterY() { return TILE_SIZE / 2; }
int Tile::getTextureId() { return this->texture->getId(); }
int Tile::getTileSize() { return TILE_SIZE; }
Item *Tile::getMineableResource() { return this->mineableResource; }
