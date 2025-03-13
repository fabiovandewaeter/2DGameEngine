#include "abilities/effects/HealEffect.hpp"

#include "iostream"
#include "entities/Entity.hpp"

void HealEffect::applyEffect(Entity *entity)
{
    std::cout << "HealEffect : " << entity->getHP() << std::endl;
    entity->onHit(-hp);
}
