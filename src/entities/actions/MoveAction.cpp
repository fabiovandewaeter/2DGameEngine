#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"

/*MoveAction::MoveAction(float goalX, float goalY, Entity *actor) : Action(actor), goalX(goalX), goalY(goalY), currentIndex(0), stuckedCount(0), lastPosition({0, 0})
{
    // TODO: find best value for threshold
    this->path = AstarPathFinding::findPath(this->actor->getMap(), actor->getPositionX(), actor->getPositionY(), goalX, goalY);
    this->threshold = (this->actor->getMap()->getChunk(this->goalX, this->goalY)->isStructure(this->goalX, this->goalY)) ? this->actor->getRange() + 1 : 0.04 + 0.0001f; // don't know why 0.04
}

void MoveAction::update()
{
    if (this->currentIndex >= this->path.size())
    {
        this->completed = true;
        return;
    }

    // On stocke la position actuelle pour détecter le déplacement
    float moveDelta = std::sqrt(std::pow(this->actor->getPositionX() - this->lastPosition.x, 2) + std::pow(this->actor->getPositionY() - this->lastPosition.y, 2));
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
    this->lastPosition = {this->actor->getPositionX(), this->actor->getPositionY()};

    // Si l'entité est bloquée pendant trop longtemps, on relance le pathfinding
    if (this->stuckedCount >= 60)
    {
        this->completed = true;
        this->actor->teleportToHome();
        return;
    }

    // Récupère la cible actuelle dans le chemin
    SDL_FPoint target = this->path[currentIndex];
    float dx = target.x - this->actor->getPositionX();
    float dy = target.y - this->actor->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < this->threshold)
    {
        this->currentIndex++;
    }
    else
    {
        float dirX = dx / distance;
        float dirY = dy / distance;
        this->actor->moveBy(dirX * this->actor->getSpeed(), dirY * this->actor->getSpeed());
    }
}*/

MoveAction::MoveAction(float goalX, float goalY, Entity *actor) : Action(actor), goalX(goalX), goalY(goalY), currentIndex(0), stuckedCount(0), lastPosition({0, 0})
{
    path = AstarPathFinding::findPath(actor->getMap(), actor->getPositionX(), actor->getPositionY(), goalX, goalY);
    threshold = (actor->getMap()->getChunk(goalX, goalY)->isStructure(goalX, goalY))
                    ? actor->getRange() + 1
                    : 0.04f + 0.0001f;
}

void MoveAction::update()
{
    // Si on a atteint la fin du chemin, l'action est terminée
    if (currentIndex >= path.size())
    {
        return;
    }

    // Calcul de la distance vers le prochain point
    float dx = path[currentIndex].x - actor->getPositionX();
    float dy = path[currentIndex].y - actor->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < threshold)
    {
        currentIndex++;
        return;
    }

    // Détection d'un éventuel blocage (l'entité ne se déplace pas suffisamment)
    float moveDelta = std::sqrt(std::pow(actor->getPositionX() - lastPosition.x, 2) +
                                std::pow(actor->getPositionY() - lastPosition.y, 2));
    const float minimalMovement = 0.001f;
    if (moveDelta < minimalMovement)
    {
        stuckedCount++;
    }
    else
    {
        stuckedCount = 0;
    }
    lastPosition = {actor->getPositionX(), actor->getPositionY()};

    if (stuckedCount >= 60)
    {
        std::cerr << "MoveAction::update() : l'entité est bloquée. Téléportation au point de départ." << std::endl;
        actor->teleportToHome();
        currentIndex = path.size();
        return;
    }

    // Mouvement vers le point cible
    float dirX = dx / distance;
    float dirY = dy / distance;
    actor->moveBy(dirX * actor->getSpeed(), dirY * actor->getSpeed());
}

bool MoveAction::isCompleted() const { return currentIndex >= path.size(); }
