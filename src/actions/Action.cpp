#include "Action.hpp"

#include "effects/Effect.hpp"
#include "patterns/Pattern.hpp"

Action::Action() {}
Action::~Action() {}

void Action::apply(int x, int y)
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
}