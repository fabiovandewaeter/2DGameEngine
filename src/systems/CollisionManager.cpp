#include "CollisionManager.hpp"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::init(std::vector<Entity *> entities)
{
    this->allEntities.insert(this->allEntities.end(), entities.begin(), entities.end());
}

bool CollisionManager::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    return !(rectA.x + rectA.w <= rectB.x ||
             rectA.x >= rectB.x + rectB.w ||
             rectA.y + rectA.h <= rectB.y ||
             rectA.y >= rectB.y + rectB.h);
}

SDL_Rect CollisionManager::handleCollisionsFor(Entity *entity, int newPosX, int newPosY)
{
    SDL_Rect hitBox = entity->getHitBox();
    SDL_Rect newHitBox = {newPosX, newPosY, hitBox.w, hitBox.h};
    int size = this->allEntities.size();
    for (size_t i = 0; i < size; i++)
    {
        Entity *otherEntity = this->allEntities[i];
        if (entity != otherEntity && otherEntity->isSolid())
        {
            if (checkCollision(newHitBox, otherEntity->getHitBox()))
            {
                return hitBox;
            }
        }
    }
    return newHitBox;
}

void CollisionManager::addEntity(Entity *entity)
{
    this->allEntities.push_back(entity);
}