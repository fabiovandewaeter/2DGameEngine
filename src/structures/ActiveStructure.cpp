#include "structures/ActiveStructure.hpp"

#include "abilities/Ability.hpp"

ActiveStructure::~ActiveStructure()
{
    int size = this->abilities.size();
    for (int i = 0; i < size; i++)
    {
        delete this->abilities[i];
    }
}

void ActiveStructure::onLeftClick()
{
    this->active = !this->active;
}
