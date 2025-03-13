#include "entities/actions/AttackEntityAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/BreakStructureAction.hpp"

AttackEntityAction::AttackEntityAction(Entity *attacker, Entity *target)
    : Action(attacker), target(target), attackPerformed(false)
{
    if (!target)
    {
        std::cerr << "Error AttackEntityAction : cible nulle." << std::endl;
    }
}

void AttackEntityAction::update()
{
    if (!target || target->isDead())
    {
        attackPerformed = true;
        return;
    }
    // Vérification que l'entité est à portée pour attaquer
    float distance = calculateDistance(actor->getPositionX(), actor->getPositionY(), target->getPositionX(), target->getPositionY());
    if (distance <= actor->getRange() + 1)
    {
        actor->attack(target);
        attackPerformed = true;
    }
}

bool AttackEntityAction::isCompleted() const { return attackPerformed; }

float AttackEntityAction::calculateDistance(float sourceX, float sourceY, float goalX, float goalY)
{
    float dx = goalX - sourceX;
    float dy = goalY - sourceY;
    return std::sqrt(dx * dx + dy * dy);
}
