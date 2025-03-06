#include "entities/actions/KillEntityAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/BreakStructureAction.hpp"

void KillEntityAction::execute()
{
    std::string structureClassName = "Tree";
    std::unique_ptr<std::pair<float, float>> destination = this->entity->getMap()->findStructure(structureClassName, this->entity);
    if (destination)
    {
        this->entity->pushAction(new BreakStructureAction(destination->first, destination->second, this->entity)); // first because it's a stack
        this->entity->pushAction(new MoveAction(destination->first, destination->second, this->entity));
        // this->entity->pushAction(new MoveAction(-2,0, this->entity));
    }
    else
    {
        std::cout << "KillEntityAction::execute() : " << structureClassName << " not found on the Map" << std::endl;
    }
}
