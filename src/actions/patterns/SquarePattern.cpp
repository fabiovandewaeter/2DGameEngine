#include "SquarePattern.hpp"

#include <iostream>

SquarePattern::SquarePattern(EntityManager *entityManager, int radius) : Pattern(entityManager, radius) {}
SquarePattern::~SquarePattern() {}

std::vector<Entity *> SquarePattern::affectedEntities(int x, int y)
{
    std::cout << "SquarePattern::affectedEntities()" << std::endl;
    std::vector<Entity *> entities;
    return entities;
}