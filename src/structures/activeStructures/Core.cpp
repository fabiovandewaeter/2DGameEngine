#include "Core.hpp"

#include <iostream>
#include "../../systems/CollisionManager.hpp"
#include "../../systems/EntityManager.hpp"
#include "../../systems/TextureManager.hpp"
#include "../../entities/Entity.hpp"

Core::Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, std::vector<Texture *> *entityTextures, unsigned int HP)
{
    init(texture, collisionManager, 1, HP, true);
    this->entityManager = entityManager;
    this->entityTextures = entityTextures;
}
Core::Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, std::vector<Texture *> *entityTextures, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, collisionManager, hitBox, 1, HP, true);
    this->entityManager = entityManager;
    this->entityTextures = entityTextures;
}

void Core::update()
{
    if (isActive())
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
        SDL_Rect rect = {this->hitBox.x + 1, this->hitBox.y + 1, this->hitBox.w, this->hitBox.h};
        if (!this->collisionManager->checkCollisionWithSolidStructure(rect))
        {
            std::cout << "OUI" << std::endl;
            this->entityManager->addEntity(new Entity((*this->entityTextures)[1], rect));
        }
        else
        {
            std::cout << "NON" << std::endl;
        }
        spawnCooldownCounter = 0;
    }
    else
    {
        spawnCooldownCounter++;
    }
}