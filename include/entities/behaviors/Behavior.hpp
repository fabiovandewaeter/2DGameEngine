#ifndef behavior_hpp
#define behavior_hpp

#include "entities/Entity.hpp"

class Entity;

class Behavior
{
public:
    Behavior(Entity *entity) : entity(entity) {}
    virtual ~Behavior() = default;
    virtual void update() = 0;

protected:
    Entity *entity;
};

#endif
