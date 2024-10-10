#include "Wall.hpp"

Wall::Wall(Texture *texture, SDL_Rect hitBox, unsigned int HP, Map *map) : PassiveStructure(texture, hitBox, HP, map) {}