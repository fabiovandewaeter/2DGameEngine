#include "entities/actions/BreakStructureAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "structures/Structure.hpp"

void BreakStructureAction::execute()
{
    Chunk *chunk = this->entity->getMap()->getChunk(this->goalX, this->goalY);
    if (chunk != nullptr)
    {
        Structure* structure = chunk->breakStructure(goalX, goalY);
        if (structure != nullptr){
            this->entity->giveStructure(structure);
        }
    }
    this->completed = true;
}

bool BreakStructureAction::isCompleted() { return this->completed; }
