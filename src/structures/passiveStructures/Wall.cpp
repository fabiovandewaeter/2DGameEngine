#include "Wall.hpp"

Wall::Wall(Texture *texture, CollisionManager *collisionManager, unsigned int HP)
{
    init(texture, collisionManager, 0, HP, true);
}
Wall::Wall(Texture *texture, CollisionManager *collisionManager, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, collisionManager, hitBox, 0, HP, true);
}