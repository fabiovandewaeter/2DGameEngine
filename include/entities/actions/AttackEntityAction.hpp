#ifndef attack_entity_action_hpp
#define attack_entity_action_hpp

#include "Action.hpp"

class AttackEntityAction : public Action
{
public:
    AttackEntityAction(Entity *attacker, Entity *target);
    void execute() override;

private:
    Entity *target;

    bool isTargetInRange(Entity *attacker, Entity *target);
};

#endif
