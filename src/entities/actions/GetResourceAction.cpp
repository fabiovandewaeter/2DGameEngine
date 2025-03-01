#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"

void GetResourceAction::execute(Entity *entity)
{
    std::vector<SDL_Point> path;
    this->astarPathFinding->findPath(entity->getMap(), 0, 0, 10, 10, &path);
    entity->pushAction(new MoveAction(path));
}

bool GetResourceAction::isCompleted() { return false; }
