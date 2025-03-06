#include "entities/actions/BreakStructureAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "structures/Structure.hpp"

void BreakStructureAction::execute()
{
    float threshold = this->entity->getRange() + 1;
    if (isTargetInRange(this->entity, this->goalX, this->goalY))
    {
        Chunk *chunk = this->entity->getMap()->getChunk(this->goalX, this->goalY);
        if (chunk != nullptr)
        {
            Structure *structure = chunk->breakStructure(this->goalX, this->goalY);
            if (structure != nullptr)
            {
                this->entity->giveStructure(structure);
            }
        }
    }
    else
    {
        std::cout << "ERROR BreakStructureAction::execute() : Entity not in range" << std::endl;
    }
    this->completed = true;
}

bool BreakStructureAction::isTargetInRange(Entity *attacker, float goalX, float goalY)
{
    float dx = goalX - attacker->getPositionX();
    float dy = goalY - attacker->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= attacker->getRange() + 1;
}
