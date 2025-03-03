#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"

void GetResourceAction::execute()
{
    std::string structureClassName = "Tree";
    std::unique_ptr<std::pair<float, float>> destination = this->entity->getMap()->findStructure(structureClassName);
    if (destination)
    {
        std::cout << destination->first << " " << destination->second << std::endl;
        this->entity->pushAction(new MoveAction(destination->first, destination->second, this->entity));
        /*int x = 50, y = 5;
        this->entity->pushAction(new MoveAction(x, y, this->entity));*/
    }
    else
    {
        std::cout << "GetResourceAction::execute() : " << structureClassName << " not found on the Map" << std::endl;
    }
}

bool GetResourceAction::isCompleted() { return false; }
