#ifndef state_hpp
#define state_hpp

class Entity;

class State
{
public:
    State(Entity *entity) : entity(entity) {}
    ~State() = default;

    void update();

private:
    Entity *entity;
};

#endif
