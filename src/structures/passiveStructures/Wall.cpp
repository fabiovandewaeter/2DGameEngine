#include "Wall.hpp"

Wall::Wall(Texture *texture, unsigned int HP)
{
    init(texture, HP, true);
}
Wall::Wall(Texture *texture, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, hitBox, HP, true);
}