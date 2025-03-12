#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"

MoveAction::MoveAction(float goalX, float goalY, Entity *entity) : Action(entity), goalX(goalX), goalY(goalY), currentIndex(0), stuckedCount(0), lastPosition({0, 0})
{
    // TODO: find best value for threshold
    this->path = AstarPathFinding::findPath(this->entity->getMap(), entity->getPositionX(), entity->getPositionY(), goalX, goalY);
    this->threshold = (this->entity->getMap()->getChunk(this->goalX, this->goalY)->isStructure(this->goalX, this->goalY)) ? this->entity->getRange() + 1 : 0.04 + 0.0001f; // don't know why 0.04
}

void MoveAction::execute()
{
    if (this->currentIndex >= this->path.size())
    {
        this->completed = true;
        return;
    }

    // On stocke la position actuelle pour détecter le déplacement
    float moveDelta = std::sqrt(std::pow(this->entity->getPositionX() - this->lastPosition.x, 2) + std::pow(this->entity->getPositionY() - this->lastPosition.y, 2));
    const float minimalMovement = 0.001f; // Seuil de déplacement minimal

    // Si l'entité n'a pas bougé suffisamment, on incrémente stuckedCount
    if (moveDelta < minimalMovement)
    {
        this->stuckedCount++;
    }
    else
    {
        this->stuckedCount = 0; // Réinitialiser si l'entité progresse
    }
    this->lastPosition = {this->entity->getPositionX(), this->entity->getPositionY()};

    // Si l'entité est bloquée pendant trop longtemps, on relance le pathfinding
    if (this->stuckedCount >= 60)
    {
        this->completed = true;
        this->entity->teleportToHome();
        return;
    }

    // Récupère la cible actuelle dans le chemin
    SDL_FPoint target = this->path[currentIndex];
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
