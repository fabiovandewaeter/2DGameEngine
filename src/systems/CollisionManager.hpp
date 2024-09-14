#ifndef collision_manager_hpp
#define collision_manager_hpp

#include <SDL.h>
#include <vector>
#include "../entities/Entity.hpp"
#include "../map/Map.hpp"
#include "../objects/staticObjects/StaticObject.hpp"

class Entity;

class CollisionManager
{
public:
    CollisionManager();
    ~CollisionManager();

    void init(std::vector<Entity *> entities, Map *map);
    bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
    SDL_Rect handleCollisionsFor(Entity *entity, int newPosX, int newPosY);

    void addEntity(Entity *entity);
    void addEntities(std::vector<Entity*> *entities);

private:
    std::vector<Entity*> allEntities;
    Map *map;
};

#endif