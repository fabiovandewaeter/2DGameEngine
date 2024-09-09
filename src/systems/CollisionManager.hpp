#ifndef collision_manager_hpp
#define collision_manager_hpp

#include <SDL.h>
#include <vector>
#include "../entities/Entity.hpp"
#include "../objects/staticObjects/StaticObject.hpp"

class Entity;

class CollisionManager
{
public:
    CollisionManager();
    ~CollisionManager();

    void init(std::vector<Entity *> entities, std::vector<StaticObject *> staticObjects);
    bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
    SDL_Rect handleCollisionsFor(Entity *entity, int newPosX, int newPosY);

    void addEntity(Entity *entity);

private:
    std::vector<Entity*> allEntities;
    std::vector<StaticObject*> allStaticObjects;
};

#endif