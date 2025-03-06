#include "abilities/effects/DamageEffect.hpp"

#include "iostream"
#include "entities/Entity.hpp"

DamageEffect::DamageEffect(int damage) : Effect() { this->damage = damage; }
DamageEffect::~DamageEffect() {}

void DamageEffect::applyEffect(Entity *entity)
{
    std::cout << "DamageEffect : " << entity->getHP() << std::endl;
    entity->onHit(damage);
}
