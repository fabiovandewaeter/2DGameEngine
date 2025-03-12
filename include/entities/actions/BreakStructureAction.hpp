#ifndef break_structure_action_hpp
#define break_structure_action_hpp

#include "Action.hpp"

class BreakStructureAction : public Action
{
public:
    BreakStructureAction(float goalX, float goalY, Entity *actor);
    void update() override;
    bool isCompleted() const override;

private:
    float goalX, goalY;
    bool structureBroken;
};

#endif
