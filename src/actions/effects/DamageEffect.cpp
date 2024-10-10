#include "DamageEffect.hpp"

#include "../../entities/Entity.hpp"
#include "iostream"

DamageEffect::DamageEffect(int damage) : Effect() { this->damage = damage; }
DamageEffect::~DamageEffect() {}

void DamageEffect::applyEffect(Entity *entity)
{
    std::cout << entity->getHP() << std::endl;
    entity->hit(damage);
}
