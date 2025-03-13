#ifndef explorer_behavior_hpp
#define explorer_behavior_hpp

#include "entities/behaviors/Behavior.hpp"

class ExplorerBehavior : public Behavior
{
public:
    ExplorerBehavior(Entity *entity) : Behavior(entity) {}
    void update() override;

private:
};

#endif
