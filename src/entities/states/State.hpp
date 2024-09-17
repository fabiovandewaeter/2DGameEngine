#ifndef state_hpp
#define state_hpp

#include "../Entity.hpp"

class State{
public:
    State(Entity *entity);
    ~State();
    
    void update();
private:
    Entity *entity;
};

#endif