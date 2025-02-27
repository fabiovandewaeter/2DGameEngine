#ifndef warrior_behavior_hpp
#define warrior_behavior_hpp

#include "entities/behaviors/Behavior.hpp"

class WarriorBehavior : public Behavior
{
public:
    void execute(Entity *entity) override;

private:
};

#endif
