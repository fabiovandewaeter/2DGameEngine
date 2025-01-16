#ifndef entity_manager_hpp
#define entity_manager_hpp

#include <SDL2/SDL.h>
#include <vector>

class Camera;
class CollisionManager;
class Texture;
class Entity;
class Player;

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void init(Camera *camera, CollisionManager *collisionManager, std::vector<Texture *> *entityTextures);
    void loadEntities();
    void update();
    void render();

    void addPlayer(Player *player);
    void addEntity(Entity *entity);
    bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
    std::vector<Entity *> getEntities();
    std::vector<Entity *> getPotentialEntities(Entity *entity);
    std::vector<Entity *> getEntitiesInArea(SDL_Rect area);
    Entity *generateDefaultEntity(SDL_Rect hitBox);
    Player *getPlayer();

private:
    Player *player;
    std::vector<Entity *> entities;
    CollisionManager *collisionManager;
    std::vector<Texture *> *entityTextures;
    Camera *camera;
};

#endif
