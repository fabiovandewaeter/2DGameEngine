#include "Core.hpp"

#include <iostream>
#include "../../systems/CollisionManager.hpp"
#include "../../systems/EntityManager.hpp"
#include "../../systems/TextureManager.hpp"
#include "../../entities/Entity.hpp"

Core::Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, unsigned int HP)
{
    init(texture, collisionManager, entityManager, map, (SDL_Rect){-1, -1, -1, -1}, HP);
}
Core::Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, collisionManager, entityManager, map, hitBox, HP);
}

void Core::update()
{
    if (this->active)
    {
        spawnEntities();
    }
}
const int SPAWN_COOLDOWN = 100;
int spawnCooldownCounter = 0;
void Core::spawnEntities()
{
    if (spawnCooldownCounter >= SPAWN_COOLDOWN)
    {
        std::vector<SDL_Rect> potentialSpawnTiles = this->getPotentialSpawnTiles();
        int size = potentialSpawnTiles.size();
        bool finished = false;
        int i = 0;
        while (i < size && !finished)
        {
            if (!this->collisionManager->checkCollisionWithSolidStructure(potentialSpawnTiles[i]))
            {
                std::cout << "OUI" << std::endl;
                this->entityManager->addEntity(this->entityManager->generateDefaultEntity(potentialSpawnTiles[i]));
                finished = true;
            }
            else
            {
                std::cout << "NON" << std::endl;
            }
            i++;
        }
        spawnCooldownCounter = 0;
    }
    else
    {
        spawnCooldownCounter++;
    }
}
void Core::onClick()
{
    std::cout << "CLICK" << std::endl;
    this->active = !this->active;
}