#include "abilities/Ability.hpp"

#include "abilities/patterns/Pattern.hpp"
#include "abilities/effects/Effect.hpp"
#include "systems/core/TickManager.hpp"

Ability::~Ability()
{
    delete pattern;
    int size = this->effects.size();
    for (int i = 0; i < size; i++)
    {
        delete this->effects[i];
    }
}

void Ability::apply(int positionX, int positionY)
{
    if ((tickManager->getTicks() - cooldownStartTick) > cooldown)
    {
        std::vector<Entity *> entities = pattern->getAffectedEntities(positionX, positionY);
        int size = entities.size();
        int sizeEffectsList = effects.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < sizeEffectsList; j++)
            {
                effects[j]->applyEffect(entities[i]);
            }
        }
        cooldownStartTick = tickManager->getTicks();
    }
}
