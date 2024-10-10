#include "Effect.hpp"

Effect::Effect() {}
Effect::~Effect() {}

void Effect::applyEffect(std::vector<Entity *> entities)
{
    int size = entities.size();
    for (int i = 0; i < size; i++)
    {
        applyEffect(entities[i]);
    }
}