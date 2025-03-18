#include "abilities/patterns/SquarePattern.hpp"

#include <iostream>
#include "systems/game_objects/EntityManager.hpp"

SquarePattern::SquarePattern(EntityManager *entityManager, int radius) : Pattern(entityManager, radius) {}
SquarePattern::~SquarePattern() {}

std::vector<Entity *> SquarePattern::getAffectedEntities(int positionX, int positionY)
{
	SDL_FRect pattern = {(float)(positionX - (radius / 2)),(float)(positionY - (radius / 2)),(float) radius, (float)radius};
    return entityManager->getEntitiesInArea(pattern);
}
