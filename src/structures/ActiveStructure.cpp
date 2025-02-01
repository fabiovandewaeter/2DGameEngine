#include "structures/ActiveStructure.hpp"

#include "actions/Action.hpp"

ActiveStructure::~ActiveStructure()
{
    int size = this->actions.size();
    for (int i = 0; i < size; i++)
    {
        delete this->actions[i];
    }
}

void ActiveStructure::onLeftClick()
{
    this->active = !this->active;
}
