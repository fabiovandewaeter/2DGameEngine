#include "Core.hpp"

#include "../../systems/CollisionManager.hpp"
#include <iostream>

Core::Core(Texture *texture, CollisionManager *collisionManager, unsigned int HP)
{
    init(texture, collisionManager, 1, HP, true);
}
Core::Core(Texture *texture, CollisionManager *collisionManager, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, collisionManager, hitBox, 1, HP, true);
}

void Core::update()
{
    if (isActive())
    {
        spawnEntities();
    }
}
void Core::spawnEntities()
{
    SDL_Rect rect = {this->hitBox.x-1, this->hitBox.y, this->hitBox.w, this->hitBox.h};
    if (! this->collisionManager->checkCollisionWithSolidStructure(rect)){
        std::cout << "OUI" << std::endl;
    }
    else{
        std::cout << "NON" << std::endl;
    }
}