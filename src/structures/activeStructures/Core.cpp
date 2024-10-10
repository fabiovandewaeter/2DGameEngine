#include "Core.hpp"

#include <iostream>
#include "../../systems/CollisionManager.hpp"
#include "../../systems/EntityManager.hpp"
#include "../../systems/TextureManager.hpp"
#include "../../entities/Entity.hpp"
#include "../../Map/Map.hpp"

Core::Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP) : ActiveStructure(texture, collisionManager, entityManager, map, hitBox, HP, true) {}

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
        int i = 0;
        int size = potentialSpawnTiles.size();
        bool finished = false;
        while (i < size && !finished)
        {
            if (!this->collisionManager->checkCollisionWithSolidStructure(potentialSpawnTiles[i]))
            {
                this->entityManager->addEntity(this->entityManager->generateDefaultEntity(potentialSpawnTiles[i]));
                finished = true;
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
std::vector<SDL_Rect> Core::getPotentialSpawnTiles()
{
    int tileSize = this->map->getTileSize();
    std::vector<SDL_Rect> potentialSpawnTiles;

    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - tileSize, this->hitBox.y - tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x, this->hitBox.y - tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize, this->hitBox.y - tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize, this->hitBox.y, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize, this->hitBox.y + tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x, this->hitBox.y + tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - tileSize, this->hitBox.y + tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - tileSize, this->hitBox.y, this->hitBox.w, this->hitBox.h});

    return potentialSpawnTiles;
}
