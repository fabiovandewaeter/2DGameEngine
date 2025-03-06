#include "entities/behaviors/WarriorBehavior.hpp"

#include <iostream>

#include "entities/actions/GetResourceAction.hpp"
#include "entities/actions/KillEntityAction.hpp"

#include "entities/Entity.hpp"
#include "map/Map.hpp"
void WarriorBehavior::execute()
{
    // this->entity->pushAction(new GetResourceAction("Tree", this->entity));
    Entity *target = this->entity->getMap()->findClosestEnemy(this->entity);
    this->entity->pushAction(new KillEntityAction(this->entity, target));
}
