#ifndef break_structure_action_hpp
#define break_structure_action_hpp

#include "Action.hpp"

class BreakStructureAction : public Action
{
public:
    BreakStructureAction(float goalX, float goalY, Entity *entity) : Action(entity), goalX(goalX), goalY(goalY) {}
    void execute() override;

private:
    float goalX, goalY;

    bool isTargetInRange(Entity *attacker, float goalX, float goalY);
};

#endif
