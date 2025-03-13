#include "entities/actions/MoveAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"

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
