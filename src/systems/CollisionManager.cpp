#include "CollisionManager.hpp"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::init(std::vector<Entity *> entities, Map *map)
{
    this->allEntities.insert(this->allEntities.end(), entities.begin(), entities.end());
    this->map = map;
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
    bool collision = false;
    SDL_Rect hitBox = entity->getHitBox();
    SDL_Rect newHitBox = {newPosX, newPosY, hitBox.w, hitBox.h};
    if (this->map->isChunkGenerated(newPosX, newPosY))
    {
        int size = this->allEntities.size();
        for (int i = 0; i < size && !collision; i++)
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
        // check destination for all 4 corners of the entity
        int newX, newY;
        Chunk *chunk;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                newX = newPosX + i * hitBox.w, newY = newPosY + j * hitBox.h;
                chunk = this->map->getChunk(newX, newY);
                chunk->convertToTileCoordinates(newX, newY);
                if (chunk->isStaticObject(newX, newY))
                {
                    StaticObject *staticObject = chunk->getStaticObject(newX, newY);
                    if (staticObject->isSolid())
                    {
                        if (checkCollision(newHitBox, staticObject->getHitBox()))
                        {
                            return hitBox;
                        }
                    }
                }
            }
        }
    }
    return newHitBox;
}

void CollisionManager::addEntity(Entity *entity)
{
    this->allEntities.push_back(entity);
}
void CollisionManager::addEntities(std::vector<Entity *> *entities)
{
    int size = entities->size();
    for (int i = 0; i < size; i++)
    {
        this->allEntities.push_back((*entities)[i]);
    }
}