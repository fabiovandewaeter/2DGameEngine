#include "Pattern.hpp"

Pattern::Pattern(EntityManager *EntityManager, int radius)
{
    this->entityManager = entityManager;
    this->radius = radius;
}
Pattern::~Pattern() {}