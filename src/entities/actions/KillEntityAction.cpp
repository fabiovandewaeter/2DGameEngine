#include "entities/actions/KillEntityAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/AttackEntityAction.hpp"

KillEntityAction::KillEntityAction(Entity *attacker, Entity *target) : Action(attacker), target(target)
{
    if (target)
    {
        std::pair<float, float> destination = {this->target->getPositionX(), this->target->getPositionY()};
        this->subActions.push(new MoveAction(destination.first, destination.second, this->entity));
        this->subActions.push(new AttackEntityAction(this->entity, this->target));
    }
    else
    {
        std::cout << "ERROR KillEntityAction : no Entity found on the Map" << std::endl;
        this->completed = true;
    }
}

void KillEntityAction::execute()
{
    if (!this->target || this->target->isDead())
    {
        std::cout << "KillEntityAction::execute() : Target is dead" << std::endl;
    }
    else if (this->subActions.empty()) // reset if target is alive but not dead yet and subActions are finished
    {
        std::pair<float, float> destination = {this->target->getPositionX(), this->target->getPositionY()};
        this->subActions.push(new MoveAction(destination.first, destination.second, this->entity));
        this->subActions.push(new AttackEntityAction(this->entity, this->target));
    }
    executeSubActions();
}
