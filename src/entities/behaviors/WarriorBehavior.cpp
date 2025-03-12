#include "entities/behaviors/WarriorBehavior.hpp"

#include <iostream>

#include "entities/actions/GetResourceAction.hpp"
#include "entities/actions/KillEntityAction.hpp"

#include "entities/Entity.hpp"
#include "map/Map.hpp"
int a = 0;
void WarriorBehavior::update()
{
    // this->entity->pushAction(new GetResourceAction("Tree", this->entity));
    Entity *target = this->entity->getMap()->findClosestEnemy(this->entity);
    this->entity->pushAction(new KillEntityAction(this->entity, target));
    if (a > 0)
    {
        exit(1);
    }
    a++;
}
