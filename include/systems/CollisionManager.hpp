#ifndef collision_manager_hpp
#define collision_manager_hpp

#include <SDL2/SDL.h>
#include <vector>

class Map;
class EntityManager;
class Entity;

class CollisionManager
{
public:
    CollisionManager(Map *map) : map(map), entityManager(map->getEntityManager()) {};
    ~CollisionManager();

    // returns true if there is a collision
    bool checkRectanglesCollision(SDL_Rect rectA, SDL_Rect rectB);
    bool isPointInCollisionWithRectangle(int x, int y, SDL_Rect rect);
    bool isRectangleInCollisionWithSolidStructure(SDL_Rect rect);
    SDL_Rect handleCollisionsFor(Entity *entity, int newPosX, int newPosY);

private:
    Map *map;
    EntityManager *entityManager;
};

#endif
