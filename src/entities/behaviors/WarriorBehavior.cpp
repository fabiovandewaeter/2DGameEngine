#include "entities/behaviors/WarriorBehavior.hpp"

#include <iostream>

#include "entities/actions/GetResourceAction.hpp"

void WarriorBehavior::execute()
{
    this->entity->pushAction(new GetResourceAction("Tree", this->entity));
}
