#include "Wall.hpp"

Wall::Wall(Texture *texture, SDL_Rect hitBox)
{
    init(texture, hitBox, "Wall", 100);
}
Wall::~Wall() {}