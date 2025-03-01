#include "entities/behaviors/WarriorBehavior.hpp"

#include "entities/actions/GetResourceAction.hpp"

#include <iostream>
void WarriorBehavior::execute(Entity *entity)
{
    this->getResourceAction->execute(entity);
}
