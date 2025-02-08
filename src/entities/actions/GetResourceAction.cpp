#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "entities/Entity.hpp"
#include "map/Map.hpp"

void GetResourceAction::execute(Entity *entity)
{
    AstarPathFinding *astarPathFinding = new AstarPathFinding();
    std::vector<SDL_Point> liste;
    astarPathFinding->findPath(entity->getMap(), 0, 0, 100, 200, &liste);
    // liste = astarPathFinding->findPath(this->map, 0, 0, 1000, 2000);
    int size = liste.size();
    for (int i = 0; i < size; i++)
    {
        std::cout << "x: " << liste[i].x << " y: " << liste[i].y << std::endl;
    }
}

bool GetResourceAction::isCompleted()
{
    return false;
}
