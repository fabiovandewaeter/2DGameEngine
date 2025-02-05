#include "actions/effects/HealEffect.hpp"

#include "iostream"
#include "entities/Entity.hpp"

HealEffect::HealEffect(int hp) : Effect() { this->hp = hp; }
HealEffect::~HealEffect() {}

void HealEffect::applyEffect(Entity *entity)
{
    std::cout << "HealEffect : " << entity->getHP() << std::endl;
    entity->hit(-this->hp);
}
