#include "entities/behaviors/WarriorBehavior.hpp"

#include <iostream>

#include "entities/actions/GetResourceAction.hpp"
#include "entities/actions/KillEntityAction.hpp"

#include "entities/Entity.hpp"
#include "map/Map.hpp"
void WarriorBehavior::update()
{
    Entity *target = entity->getMap()->findClosestEnemy(entity);
    entity->pushAction(new KillEntityAction(entity, target));
}
