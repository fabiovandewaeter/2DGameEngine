#include "structures/ActiveStructure.hpp"

#include "abilities/Ability.hpp"

ActiveStructure::~ActiveStructure()
{
    int size = abilities.size();
    for (int i = 0; i < size; i++)
    {
        delete abilities[i];
    }
}

void ActiveStructure::onLeftClick()
{
    active = !active;
}
