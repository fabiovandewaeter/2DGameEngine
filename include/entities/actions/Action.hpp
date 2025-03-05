#ifndef action_hpp
#define action_hpp

#include <string>

#include "entities/Entity.hpp"

class Entity;

class Action
{
public:
    Action(Entity *entity) : entity(entity) {}
    ~Action() = default;
    virtual void execute() = 0;
    virtual bool isCompleted() = 0;

protected:
    Entity *entity;
};

#endif
