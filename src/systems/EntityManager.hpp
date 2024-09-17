#ifndef entity_manager_hpp
#define entity_manager_hpp

#include <vector>
#include "../entities/Entity.hpp"
#include "CollisionManager.hpp"
#include "Camera.hpp"

class Entity;

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void init(Camera *camera, CollisionManager *collisionManager, std::vector<Texture *> *entityTextures);
    void loadEntities();
    void update();
    void render();

    void addEntity(Entity *entity);
    std::vector<Entity *> getPotentialEntities(Entity *entity);

private:
    std::vector<Entity *> entities;
    CollisionManager *collisionManager;
    std::vector<Texture *> *entityTextures;
    Camera *camera;
};

#endif