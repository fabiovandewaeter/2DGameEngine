#include "entities/actions/MoveAction.hpp"

#include "entities/Entity.hpp"
#include "map/Map.hpp"

void MoveAction::execute(Entity *entity)
{
    if (currentIndex >= this->path->size())
        return; // Action terminée

    // On récupère la position cible (centre de la tile, en pixels)
    SDL_Point target = (*this->path)[currentIndex];

    // On calcule la direction entre la position actuelle et la cible
    float dx = target.x - entity->getPositionX();
    float dy = target.y - entity->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);

    // Seuil pour considérer que la cible est atteinte
    const float threshold = 2.0f;
    if (distance < threshold)
    {
        // On passe à la case suivante du chemin
        currentIndex++;
    }
    else
    {
        // Calcul de la direction normalisée
        float dirX = dx / distance;
        float dirY = dy / distance;
        // Mise à jour de la position via, par exemple, un setter ou une méthode interne
        // Ici, nous supposons que Entity possède une méthode move(deltaX, deltaY)
        entity->moveBy(dirX * entity->getSpeed(), dirY * entity->getSpeed());
    }
}

bool MoveAction::isCompleted()
{
    return currentIndex >= this->path->size();
}
