#ifndef entity_manager_hpp
#define entity_manager_hpp

#include <SDL2/SDL.h>
#include <vector>

class Map;
class Camera;
class Entity;
class Player;

class EntityManager
{
public:
    EntityManager(Map *map) : map(map) {};
    ~EntityManager();

    void loadEntities();
    void update();
    void render(Camera *camera);

    void addPlayer(Player *player);
    void addEntity(Entity *entity);
    bool checkCollision(SDL_FRect rectA, SDL_FRect rectB);
    std::vector<Entity *> getEntities();
    std::vector<Entity *> getPotentialEntities(Entity *entity);
    std::vector<Entity *> getEntitiesInArea(SDL_FRect area);
    std::vector<Player *> *getPlayers();
    int getNumberOfPlayers();
    Entity *findClosestEnemy(const Entity *entity);

private:
    Map *map;
    std::vector<Entity *> entities;
    std::vector<Player *> players;
};

#endif
