#include "map/Tile.hpp"

#include "systems/core/Camera.hpp"
#include "systems/game_objects/ItemFactory.hpp"
#include "Texture.hpp"

Item *Tile::defaultMineableResource = ItemFactory::getItem("Stone");

void Tile::render(Camera *camera) { camera->render(this); }

float Tile::getPositionX() const { return positionX; }
float Tile::getPositionY() const { return positionY; }
float Tile::getCenterX() const { return TILE_PIXELS_SIZE / 2; }
float Tile::getCenterY() const { return TILE_PIXELS_SIZE / 2; }
int Tile::getTileSize() { return TILE_PIXELS_SIZE; }
Item *Tile::getMineableResource() const { return mineableResource; }
std::string Tile::getTextureName() const { return textureName; }
