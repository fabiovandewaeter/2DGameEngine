#ifndef warrior_behavior_hpp
#define warrior_behavior_hpp

#include "entities/behaviors/Behavior.hpp"
#include "entities/actions/GetResourceAction.hpp"

class WarriorBehavior : public Behavior
{
public:
    WarriorBehavior() : Behavior(), getResourceAction(new GetResourceAction("Wood")) {}
    void execute(Entity *entity) override;

private:
    GetResourceAction *getResourceAction;
};

#endif
