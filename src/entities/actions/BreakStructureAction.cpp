#include "entities/actions/BreakStructureAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "structures/Structure.hpp"

void BreakStructureAction::execute()
{
    float threshold = this->entity->getRange() + 1;
    if ((std::fabs(this->entity->getPositionX() - this->goalX) < threshold) && (std::fabs(this->entity->getPositionY() - this->goalY) < threshold))
    {
        Chunk *chunk = this->entity->getMap()->getChunk(this->goalX, this->goalY);
        if (chunk != nullptr)
        {
            Structure *structure = chunk->breakStructure(goalX, goalY);
            if (structure != nullptr)
            {
                this->entity->giveStructure(structure);
            }
        }
    }
    else
    {
        std::cout << "BreakStructureAction::execute() : Entity not in range" << std::endl;
    }
    this->completed = true;
}

bool BreakStructureAction::isCompleted() { return this->completed; }
