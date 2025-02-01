#include "map/Tile.hpp"

#include "systems/core/Camera.hpp"
#include "systems/game_objects/ItemFactory.hpp"
#include "Texture.hpp"

Item* Tile::defaultMineableResource = ItemFactory::getItem("Stone");

Tile::Tile(Texture *texture, int x, int y)
{
    this->texture = texture;
    this->x = x;
    this->y = y;
    this->mineableResource = Tile::defaultMineableResource;
}
Tile::Tile(Texture *texture, int x, int y, Item *mineableResource)
{
    this->texture = texture;
    this->x = x;
    this->y = y;
    this->mineableResource = mineableResource;
}
Tile::~Tile() {}

void Tile::render(Camera *camera)
{
    SDL_Rect renderBox = (SDL_Rect){this->x, this->y, TILE_SIZE, TILE_SIZE};
    camera->convertInGameToCameraCoordinates(renderBox);
    this->texture->render(renderBox);
}

int Tile::getCenterX() { return TILE_SIZE / 2; }
int Tile::getCenterY() { return TILE_SIZE / 2; }
int Tile::getTextureId() { return this->texture->getId(); }
int Tile::getTileSize() { return TILE_SIZE; }
Item *Tile::getMineableResource() { return this->mineableResource; }
