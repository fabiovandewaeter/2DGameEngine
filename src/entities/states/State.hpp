#ifndef state_hpp
#define state_hpp

#include "../Entity.hpp"

class State{
public:
    State();
    State(Entity *entity);
    ~State();
    
    void init(Entity *entity);
    void update();
private:
    Entity *entity;
};

#endif