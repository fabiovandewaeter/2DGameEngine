#ifndef entity_manager_hpp
#define entity_manager_hpp

#include <SDL.h>
#include <vector>

class Camera;
class CollisionManager;
class Texture;
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
    Entity *generateDefaultEntity(SDL_Rect hitBox);

private:
    std::vector<Entity *> entities;
    CollisionManager *collisionManager;
    std::vector<Texture *> *entityTextures;
    Camera *camera;
};

#endif