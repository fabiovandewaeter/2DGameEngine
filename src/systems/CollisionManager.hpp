#ifndef collision_manager_hpp
#define collision_manager_hpp

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include "../entities/Entity.hpp"

class Entity;

class CollisionManager
{
public:
    CollisionManager();
    ~CollisionManager();
    
    void init(std::vector<Entity*> entities);
    bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
    SDL_Rect handleCollisionsFor(Entity *entity, int newPosX, int newPosY);
    SDL_Rect resolveCollision(SDL_Rect &rectA, const SDL_Rect &rectB, int &dx, int &dy);

    void addEntity(Entity *entity);

private:
    std::vector<Entity*> allEntities;
};

#endif