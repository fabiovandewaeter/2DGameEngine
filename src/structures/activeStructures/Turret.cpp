#include "Turret.hpp"

#include <iostream>
#include "../../systems/CollisionManager.hpp"
#include "../../systems/EntityManager.hpp"
#include "../../systems/TextureManager.hpp"
#include "../../entities/Entity.hpp"

Turret::Turret(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP) : ActiveStructure(texture, collisionManager, entityManager, map, hitBox, HP, true) {}

void Turret::update()
{
    if (this->active)
    {
        spawnEntities();
    }
}