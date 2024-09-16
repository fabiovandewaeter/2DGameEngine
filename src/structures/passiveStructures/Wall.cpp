#include "Wall.hpp"

Wall::Wall(Texture *texture, SDL_Rect hitBox, bool solid)
{
    init(texture, hitBox, "Wall", 100, solid);
}
Wall::~Wall() {}