#include "structures/activeStructures/Turret.hpp"

#include <iostream>
#include "abilities/Ability.hpp"
#include "abilities/patterns/SquarePattern.hpp"
#include "abilities/effects/DamageEffect.hpp"
#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Turret)

void Turret::update()
{
    if (active)
    {
        int size = abilities.size();
        for (int i = 0; i < size; i++)
        {
            abilities[i]->apply(positionX + (width / 2), positionY + (height / 2));
        }
    }
}
