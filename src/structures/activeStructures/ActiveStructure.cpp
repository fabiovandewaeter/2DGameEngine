#include "ActiveStructure.hpp"

ActiveStructure::ActiveStructure(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP, bool solid) : Structure(texture, hitBox, HP, solid, map)
{
    this->collisionManager = collisionManager;
    this->entityManager = entityManager;
    this->active = true;
}
ActiveStructure::~ActiveStructure() {}

void ActiveStructure::onLeftClick()
{
    this->active = !this->active;
}