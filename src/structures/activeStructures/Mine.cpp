#include "structures/activeStructures/Mine.hpp"

#include "map/Tile.hpp"
#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Mine)

Mine::Mine() {}
Mine::Mine(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, SDL_Rect hitBox, unsigned int HP, Faction *faction, Tile *minedTile, TickManager*tickManager) : ActiveStructure(texture, collisionManager, entityManager, hitBox, HP, true, faction, tickManager)
{
    this->minedResource = minedTile->getMineableResource();
    this->capacity = 50;
    this->quantityResource = 0;
}
Mine::~Mine() {}

void Mine::update()
{
    if (this->active && (this->quantityResource < this->capacity))
    {
        quantityResource++;
    }
}

std::tuple<Item *, int> Mine::getInventory()
{
    return std::make_tuple(this->minedResource, this->quantityResource);
}
