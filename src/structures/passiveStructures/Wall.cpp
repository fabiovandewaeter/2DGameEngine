#include "structures/passiveStructures/Wall.hpp"

#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Wall)

Wall::Wall() {}
Wall::Wall(Texture *texture, SDL_Rect hitBox, unsigned int HP) : PassiveStructure(texture, hitBox, HP) {}
