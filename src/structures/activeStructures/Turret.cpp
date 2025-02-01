#include "structures/activeStructures/Turret.hpp"

#include <iostream>
#include "actions/Action.hpp"
#include "actions/patterns/SquarePattern.hpp"
#include "actions/effects/DamageEffect.hpp"
#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Turret)

void Turret::update()
{
    if (this->active)
    {
        int size = this->actions.size();
        for (int i = 0; i < size; i++)
        {
            this->actions[i]->apply(this->hitBox.x + (this->hitBox.w / 2), this->hitBox.y + (this->hitBox.h / 2));
        }
    }
}
