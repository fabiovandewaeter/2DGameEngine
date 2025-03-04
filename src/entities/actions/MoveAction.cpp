#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"

void MoveAction::execute()
{
    if (this->currentIndex >= this->path.size())
    {
        this->completed = true;
        return;
    }
    else{
        std::cout << "non" << std::endl;
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
        this->currentIndex++; // Passe à la cible suivante
    }
    else
    {
        float dirX = dx / distance;
        float dirY = dy / distance;
        this->entity->moveBy(dirX * this->entity->getSpeed(), dirY * this->entity->getSpeed());
    }
}

bool MoveAction::isCompleted() { return this->completed; }
