#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"

void MoveAction::execute()
{
    if (this->currentIndex >= this->path.size())
    {
        return;
    }
    SDL_FPoint target = this->path[this->currentIndex];

    float dx = target.x - this->entity->getPositionX();
    float dy = target.y - this->entity->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < this->threshold)
    {
        this->currentIndex++;
    }
    else
    {
        float dirX = dx / distance;
        float dirY = dy / distance;
        this->entity->moveBy(dirX * this->entity->getSpeed(), dirY * this->entity->getSpeed());
    }
}

bool MoveAction::isCompleted() { return this->currentIndex >= this->path.size(); }
