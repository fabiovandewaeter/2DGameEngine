#include "entities/actions/KillEntityAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/AttackEntityAction.hpp"

KillEntityAction::KillEntityAction(Entity *attacker, Entity *target) : Action(attacker), target(target), state(State::INIT)
{
    if (!target)
    {
        std::cerr << "ERROR : KillEntityAction => no Entity found on the Map" << std::endl;
        state = State::FINISHED;
    }
}

void KillEntityAction::update()
{
    if (!target || target->isDead())
    {
        std::cout << "KillEntityAction::execute() : Target is dead" << std::endl;
        state = State::FINISHED;
        return;
    }

    switch (state)
    {
    case State::INIT:
        moveAction = std::make_unique<MoveAction>(target->getPositionX(), target->getPositionY(), actor);
        state = State::MOVING;
        break;
    case State::MOVING:
        if (moveAction)
        {
            moveAction->update();
            float dx = target->getPositionX() - actor->getPositionX();
            float dy = target->getPositionY() - actor->getPositionY();
            float distance = std::sqrt(dx * dx + dy * dy);
            // if (moveAction->isCompleted() || (distance <= actor->getRange() + 1))
            if (moveAction->isCompleted() || (distance <= actor->getRange() + 1))
            {
                attackEntityAction = std::make_unique<AttackEntityAction>(actor, target);
                state = State::ATTACKING;
            }
        }
        break;
    case State::ATTACKING:
        if (attackEntityAction)
        {
            float dx = target->getPositionX() - actor->getPositionX();
            float dy = target->getPositionY() - actor->getPositionY();
            float distance = std::sqrt(dx * dx + dy * dy);
            if (!(distance <= actor->getRange() + 1))
            {
                moveAction = std::make_unique<MoveAction>(target->getPositionX(), target->getPositionY(), actor);
                state = State::MOVING;
                break;
            }
            attackEntityAction->update();
            if (attackEntityAction->isCompleted())
            {
                state = State::FINISHED;
            }
        }
        break;
    case State::FINISHED:
    default:
        break;
    }
}

bool KillEntityAction::isCompleted() const { return state == State::FINISHED; }
