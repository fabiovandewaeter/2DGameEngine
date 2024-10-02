#ifndef active_structure_hpp
#define active_structure_hpp

#include "../Structure.hpp"
#include <vector>

class EntityManager;
class TextureManager;
class Map;

class ActiveStructure : public Structure
{
public:
    ActiveStructure();
    ActiveStructure(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, unsigned int HP);
    ActiveStructure(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP);
    ~ActiveStructure();
    
    void init(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP);

    virtual void spawnEntities();
    std::vector<SDL_Rect> getPotentialSpawnTiles();

protected:
    EntityManager *entityManager;
    Map *map;
};

#endif