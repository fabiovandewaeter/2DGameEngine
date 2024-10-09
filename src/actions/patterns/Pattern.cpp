#include "Pattern.hpp"

#include <iostream>

Pattern::Pattern(EntityManager *entityManager, int radius)
{
    this->entityManager = entityManager;
    this->radius = radius;
}
Pattern::~Pattern() {}