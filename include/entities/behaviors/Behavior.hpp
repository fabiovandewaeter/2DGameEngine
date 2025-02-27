#ifndef behavior_hpp
#define behavior_hpp

#include "entities/Entity.hpp"

class Behavior
{
public:
    virtual ~Behavior() = default;
    virtual void execute(Entity *entity) = 0;

private:
};

#endif
