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
    CollisionManager();
    ~CollisionManager();

    void init(Map *map, EntityManager *entityManager);
    // returns true if there is a collision
    bool checkCollision(const SDL_Rect &rectA, const SDL_Rect &rectB);
    bool checkCollisionFromCoordinates(const int &x, const int &y, const SDL_Rect &rect);
    bool checkCollisionWithSolidStructure(const SDL_Rect &rect);
    SDL_Rect handleCollisionsFor(Entity *entity, const int &newPosX, const int &newPosY);

private:
    Map *map;
    EntityManager *entityManager;
};

#endif