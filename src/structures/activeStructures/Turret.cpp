#include "structures/activeStructures/Turret.hpp"

#include <iostream>
#include "abilities/Ability.hpp"
#include "abilities/patterns/SquarePattern.hpp"
#include "abilities/effects/DamageEffect.hpp"
#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Turret)

void Turret::update()
{
    if (this->active)
    {
        int size = this->abilities.size();
        for (int i = 0; i < size; i++)
        {
            this->abilities[i]->apply(this->x + (this->width / 2), this->y + (this->height / 2));
        }
    }
}
