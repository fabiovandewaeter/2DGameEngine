#ifndef explorer_behavior_hpp
#define explorer_behavior_hpp

#include "entities/behaviors/Behavior.hpp"

class ExplorerBehavior : public Behavior
{
public:
    void execute(Entity *entity) override;

private:
};

#endif
