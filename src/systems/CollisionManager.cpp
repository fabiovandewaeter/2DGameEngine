#include "CollisionManager.hpp"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::init(std::vector<Entity *> entities)
{
    this->allEntities.insert(this->allEntities.end(), entities.begin(), entities.end());
    /*for (size_t i = 0; i < entities.size(); i++){
        for (size_t j = 0; j < entities.size(); i++)
        {
            if (i != j)
            {
                this->potentialCollisions[entities[i]].push_back(entities[j]);
            }
        }
    }*/
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
    for (size_t i = 0; i < this->allEntities.size(); i++)
    {
        Entity *otherEntity = this->allEntities[i];
        if (entity != otherEntity)
        {
            SDL_Rect newHitBox = {newPosX, newPosY, hitBox.w, hitBox.h};
            if (checkCollision(newHitBox, otherEntity->getHitBox()))
            {
                //return resolveCollision(hitBox, otherEntity->getHitBox(), newPosX, newPosY);
                return hitBox;
            }
            else
            {
                return newHitBox;
            }
        }
    }
}

/*SDL_Rect CollisionManager::resolveCollision(SDL_Rect rectA, const SDL_Rect rectB, int newPosX, int newPosY)
{
    SDL_Rect newRectA = {newPosX, newPosY, rectA.w, rectA.h};
    SDL_Rect res = rectA;
    bool success = true;

    if (newRectA.x + newRectA.w <= rectB.x)
    {
        res.x = rectB.x;
        success = false;
        printf("djazuid\n");
    }
    if (newRectA.x >= rectB.x + rectB.w)
    {
        res.x = rectB.x + rectB.w;
        success = false;
        printf("djazuid\n");
    }
    if (newRectA.y + newRectA.h <= rectB.y)
    {
        res.y = rectB.y;
        success = false;
        printf("djazuid\n");
    }
    if (newRectA.y >= rectB.y + rectB.h)
    {
        res.y = rectB.y + rectB.h;
        success = false;
        printf("djazuid\n");
    }
    
    if (success){
        res.x = newRectA.x;
        res.y = newRectA.y;
    }
    else {
        printf("djazuid\n");
    }

    return res;
}*/

void CollisionManager::addEntity(Entity *entity)
{
    this->allEntities.push_back(entity);
}