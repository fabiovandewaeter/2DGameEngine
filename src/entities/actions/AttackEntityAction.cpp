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
    float dx = target->getPositionX() - actor->getPositionX();
    float dy = target->getPositionY() - actor->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance <= actor->getRange() + 1)
    {
        actor->attack(target);
        attackPerformed = true;
    }
}

bool AttackEntityAction::isCompleted() const { return attackPerformed; }
