#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"

void GetResourceAction::execute(Entity *entity)
{
    AstarPathFinding *astarPathFinding = new AstarPathFinding();
    std::vector<SDL_Point> path;
    astarPathFinding->findPath(entity->getMap(), 0, 0, 100, 200, &path);
    entity->pushAction(new MoveAction(path));
}

bool GetResourceAction::isCompleted()
{
    return false;
}
