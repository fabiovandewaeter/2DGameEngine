#include "Wall.hpp"

Wall::Wall(Texture *texture, unsigned int HP)
{
    init(texture, 0, HP, true);
}
Wall::Wall(Texture *texture, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, hitBox, 0, HP, true);
}