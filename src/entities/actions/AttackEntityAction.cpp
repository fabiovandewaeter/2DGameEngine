#include "entities/actions/AttackEntityAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/BreakStructureAction.hpp"

AttackEntityAction::AttackEntityAction(Entity *attacker, Entity *target) : Action(attacker), target(target)
{
    if (target)
    {
        float threshold = this->entity->getRange() + 1;
        if (isTargetInRange(this->entity, this->target))
        {
            this->entity->attack(this->target);
        }
    }
    else
    {
        std::cout << "Error BreakStructureAction::execute() : Entity not in range" << std::endl;
    }
}

void AttackEntityAction::execute()
{
    if (!this->target || this->target->isDead())
    {
        std::cout << "AttackEntityAction::execute() : Target is dead" << std::endl;
    }
    executeSubActions();
}

bool AttackEntityAction::isTargetInRange(Entity *attacker, Entity *target)
{
    float dx = target->getPositionX() - attacker->getPositionX();
    float dy = target->getPositionY() - attacker->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= attacker->getRange() + 1;
}
