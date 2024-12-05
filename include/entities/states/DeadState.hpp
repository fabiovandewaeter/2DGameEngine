#ifndef dead_state_hpp
#define dead_state_hpp

#include "State.hpp"

class DeadState : public State
{
public:
    DeadState();
    DeadState(Entity *entity);
    ~DeadState();
private:
};

#endif