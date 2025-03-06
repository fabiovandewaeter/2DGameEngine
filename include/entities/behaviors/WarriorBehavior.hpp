#ifndef warrior_behavior_hpp
#define warrior_behavior_hpp

#include "entities/behaviors/Behavior.hpp"
#include "entities/actions/GetResourceAction.hpp"

class WarriorBehavior : public Behavior
{
public:
    WarriorBehavior(Entity *entity) : Behavior(entity) {}
    void execute() override;

private:
};

#endif
