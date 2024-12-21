#include "map/Tile.hpp"

#include "systems/Camera.hpp"
#include "systems/ItemManager.hpp"
#include "Texture.hpp"

Item* Tile::defaultMineableResource = ItemManager::getItem("Stone");

Tile::Tile(Texture *texture, int x, int y)
{
    Tile(texture, x, y, Tile::defaultMineableResource);
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
    std::cout << "test3" << std::endl;
}

int Tile::getCenterX() { return TILE_SIZE / 2; }
int Tile::getCenterY() { return TILE_SIZE / 2; }
int Tile::getTextureId() { return this->texture->getId(); }
int Tile::getTileSize() { return TILE_SIZE; }
Item *Tile::getMineableResource() { return this->mineableResource; }
