#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "structures/Structure.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/BreakStructureAction.hpp"

GetResourceAction::GetResourceAction(std::string resourceToGet, Entity *entity) : Action(entity), resourceToGet(resourceToGet)
{
    Structure *targetedStructure = this->entity->getMap()->findClosestStructure(this->resourceToGet, this->entity);
    if (targetedStructure)
    {
        std::pair<float, float> destination = {targetedStructure->getPositionX(), targetedStructure->getPositionY()};
        this->subActions.push(new MoveAction(destination.first, destination.second, this->entity));
        this->subActions.push(new BreakStructureAction(destination.first, destination.second, this->entity));
    }
    else
    {
        std::cout << "GetResourceAction::execute() : " << this->resourceToGet << " not found on the Map" << std::endl;
        this->completed = true;
    }
}

void GetResourceAction::execute() { executeSubActions(); }
