#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"

void GetResourceAction::execute()
{
    entity->pushAction(new MoveAction(-10, 1, this->entity));
}

bool GetResourceAction::isCompleted() { return false; }
