#include "structures/activeStructures/Mine.hpp"

Mine::Mine(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, SDL_Rect hitBox, unsigned int HP, Faction *faction, Tile *minedTile) : ActiveStructure(texture, collisionManager, entityManager, hitBox, HP, true, faction)
{
    this->minedResource = minedTile->getResource();
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
