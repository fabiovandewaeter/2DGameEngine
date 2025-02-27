#include "abilities/Ability.hpp"

#include "abilities/patterns/Pattern.hpp"
#include "abilities/effects/Effect.hpp"
#include "systems/core/TickManager.hpp"

Ability::Ability(Pattern *pattern, std::vector<Effect *> effects, Uint64 cooldown, TickManager *tickManager)
{
    this->pattern = pattern;
    this->effects = effects;
    this->cooldown = cooldown;
    this->cooldownStartTick = 0;
    this->tickManager = tickManager;
}
Ability::~Ability()
{
    delete pattern;
    int size = this->effects.size();
    for (int i = 0; i < size; i++)
    {
        delete this->effects[i];
    }
}

void Ability::apply(int x, int y)
{
    if ((this->tickManager->getTicks() - this->cooldownStartTick) > this->cooldown)
    {
        std::vector<Entity *> entities = this->pattern->getAffectedEntities(x, y);
        int size = entities.size();
        int sizeEffectsList = this->effects.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < sizeEffectsList; j++)
            {
                this->effects[j]->applyEffect(entities[i]);
            }
        }
        this->cooldownStartTick = this->tickManager->getTicks();
    }
}
