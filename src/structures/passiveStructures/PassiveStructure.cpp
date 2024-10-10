#include "PassiveStructure.hpp"

#include "../../map/Map.hpp"
#include "../../map/Chunk.hpp"

PassiveStructure::PassiveStructure(Texture *texture, SDL_Rect hitBox, unsigned int HP, Map *map) : Structure(texture, hitBox, HP, true, map) {}

void PassiveStructure::onRightClick()
{
    int x = this->hitBox.x;
    int y = this->hitBox.y;
    this->map->getChunk(x, y)->destroyStructure(x, y);
}