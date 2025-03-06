#ifndef kill_entity_action_hpp
#define kill_entity_action_hpp

#include "Action.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"

class KillEntityAction : public Action
{
public:
    KillEntityAction(std::string resourceToGet, Entity *attacker, Entity *target) : Action(entity), target(target) {}
    void execute() override;

private:
    Entity *target;
};

#endif
