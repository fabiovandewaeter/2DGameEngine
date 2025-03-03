#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"

void MoveAction::execute()
{
    if (currentIndex >= this->path.size())
    {
        return;
    }
    SDL_Point target = this->path[currentIndex];

    float dx = target.x - this->entity->getPositionX();
    float dy = target.y - this->entity->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);
    std::cout << currentIndex << " " << target.x << " " << target.y << std::endl;

    const float threshold = 2.0f;
    if (distance < threshold)
    {
        currentIndex++;
    }
    else
    {
        float dirX = dx / distance;
        float dirY = dy / distance;
        this->entity->moveBy(dirX * this->entity->getSpeed(), dirY * this->entity->getSpeed());
    }
}

bool MoveAction::isCompleted() { return currentIndex >= this->path.size(); }
