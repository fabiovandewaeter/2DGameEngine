#ifndef core_hpp
#define core_hpp

#include "ActiveStructure.hpp"


class Core : public ActiveStructure
{
public:
    Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, unsigned int HP);
    Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP);

    void update();
    void spawnEntities();
    void onClick();
};

#endif