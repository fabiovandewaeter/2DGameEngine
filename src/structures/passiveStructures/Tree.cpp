#include "structures/passiveStructures/Tree.hpp"

#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Tree)

void Tree::onRightClick() { destroyed = true; }
