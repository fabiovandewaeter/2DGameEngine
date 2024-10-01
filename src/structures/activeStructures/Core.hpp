#ifndef core_hpp
#define core_hpp

#include "../Structure.hpp"

class Core : public Structure
{
public:
    Core(Texture *texture, CollisionManager *collisionManager, unsigned int HP);
    Core(Texture *texture, CollisionManager *collisionManager, SDL_Rect hitBox, unsigned int HP);

    void update();
    void spawnEntities();

private:
};

#endif