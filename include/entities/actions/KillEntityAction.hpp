#ifndef kill_entity_action_hpp
#define kill_entity_action_hpp

#include "Action.hpp"

class KillEntityAction : public Action
{
public:
    KillEntityAction(Entity *attacker, Entity *target);
    void execute() override;

private:
    Entity *target;
};

#endif
