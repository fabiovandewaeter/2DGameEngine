#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"

void MoveAction::execute(Entity *entity)
{
    if (currentIndex >= this->path.size())
    {
        return;
    }
    SDL_Point target = this->path[currentIndex];

    float dx = target.x - entity->getPositionX();
    float dy = target.y - entity->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);

    const float threshold = 2.0f;
    if (distance < threshold)
    {
        currentIndex++;
    }
    else
    {
        float dirX = dx / distance;
        float dirY = dy / distance;
        entity->moveBy(dirX * entity->getSpeed(), dirY * entity->getSpeed());
    }
}

bool MoveAction::isCompleted() { return currentIndex >= this->path.size(); }
