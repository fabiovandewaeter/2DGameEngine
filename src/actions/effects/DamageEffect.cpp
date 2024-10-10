#include "DamageEffect.hpp"

#include "../../entities/Entity.hpp"

DamageEffect::DamageEffect(int damage) : Effect() { this->damage = damage; }
DamageEffect::~DamageEffect() {}

void DamageEffect::applyEffect(Entity *entity)
{
    entity->hit(damage);
}
