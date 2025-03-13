#ifndef attack_entity_action_hpp
#define attack_entity_action_hpp

#include "Action.hpp"

class AttackEntityAction : public Action
{
public:
    AttackEntityAction(Entity *attacker, Entity *target);
    void update() override;
    bool isCompleted() const override;

private:
    Entity *target;
    bool attackPerformed;
};

#endif
