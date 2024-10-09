#include "Wall.hpp"

Wall::Wall(Texture *texture, SDL_Rect hitBox, unsigned int HP) : Structure(texture, hitBox, HP, true) {}