#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/BreakStructureAction.hpp"

GetResourceAction::GetResourceAction(std::string resourceToGet, Entity *entity) : Action(entity), resourceToGet(resourceToGet)
{
    std::unique_ptr<std::pair<float, float>> destination = this->entity->getMap()->findStructure(this->resourceToGet, this->entity);
    if (destination)
    {
        this->subActions.push(new MoveAction(destination->first, destination->second, this->entity));
        this->subActions.push(new BreakStructureAction(destination->first, destination->second, this->entity));
    }
    else
    {
        std::cout << "GetResourceAction::execute() : " << this->resourceToGet << " not found on the Map" << std::endl;
        this->completed = true;
    }
}

void GetResourceAction::execute()
{
    std::cout << "GetResourceAction::execute()" << std::endl;
    if (this->subActions.empty())
    {
        std::cout << "GetResourceAction::execute() empty" << std::endl;
        this->completed = true;
    }
    else
    {
        std::cout << "GetResourceAction::execute() NON empty" << this->subActions.size() << std::endl;
        Action *currentSubAction = this->subActions.front();
        currentSubAction->execute();
        if (currentSubAction->isCompleted())
        {
            std::cout << "GetResourceAction::execute() subAction completed" << std::endl;
            delete currentSubAction;
            this->subActions.pop();
        }
    }
}
