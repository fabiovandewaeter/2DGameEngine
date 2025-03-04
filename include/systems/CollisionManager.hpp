#ifndef collision_manager_hpp
#define collision_manager_hpp

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

class Map;
class EntityManager;
class Entity;

class CollisionManager
{
public:
    CollisionManager(Map *map) : map(map) {};
    ~CollisionManager();

    // returns true if there is a collision
    bool checkRectanglesCollision(SDL_FRect rectA, SDL_FRect rectB);
    bool isPointInCollisionWithRectangle(float x, float y, SDL_FRect rect);
    bool isRectangleInCollisionWithSolidStructure(SDL_FRect rect);
    // returns a SDL_Rect with valid position for the Entity
    SDL_FRect handleCollisionsForEntity(Entity *entity, float newPosX, float newPosY);

private:
    Map *map;
};

#endif
