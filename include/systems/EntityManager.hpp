#ifndef entity_manager_hpp
#define entity_manager_hpp

#include <SDL2/SDL.h>
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
    bool checkCollision(const SDL_Rect &rectA, const SDL_Rect &rectB);
    std::vector<Entity *> getEntities();
    std::vector<Entity *> getPotentialEntities(Entity *entity);
    std::vector<Entity *> getEntitiesInArea(const SDL_Rect &area);
    Entity *generateDefaultEntity(const SDL_Rect &hitBox);

private:
    std::vector<Entity *> entities;
    CollisionManager *collisionManager;
    std::vector<Texture *> *entityTextures;
    Camera *camera;
};

#endif