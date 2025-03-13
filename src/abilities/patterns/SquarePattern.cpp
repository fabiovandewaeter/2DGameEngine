#include "abilities/patterns/SquarePattern.hpp"

#include <iostream>
#include "systems/game_objects/EntityManager.hpp"

SquarePattern::SquarePattern(EntityManager *entityManager, int radius) : Pattern(entityManager, radius) {}
SquarePattern::~SquarePattern() {}

std::vector<Entity *> SquarePattern::getAffectedEntities(int positionX, int positionY) { return entityManager->getEntitiesInArea((SDL_FRect){positionX - (radius / 2), positionY - (radius / 2), radius, radius}); }
