#include "abilities/effects/DamageEffect.hpp"

#include "iostream"
#include "entities/Entity.hpp"

void DamageEffect::applyEffect(Entity *entity)
{
    std::cout << "DamageEffect : " << entity->getHP() << std::endl;
    entity->onHit(damage);
}
